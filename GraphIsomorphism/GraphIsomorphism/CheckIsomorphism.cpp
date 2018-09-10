#include "CheckIsomorphism.h"

bool CheckIsomorphism::check()
{
	if (this->_graph1.vertexNumb != this->_graph2.vertexNumb)
		return false;

	int tmp = 1,
		k = this->_graph1.vertexNumb,
		deg = this->_graph1.sortedDeg[0];
	//find vertex degree that occurs the least number of times
	for (int i = 1; i < this->_graph1.vertexNumb; i++) {
		if (this->_graph1.sortedDeg[i] != this->_graph2.sortedDeg[i])                  //check if vertex degrees are different in graphs
			return false;
		if (this->_graph1.sortedDeg[i] == this->_graph1.sortedDeg[i - 1])
			tmp++;
		else {
			if (k >= tmp) {
				k = tmp;
				deg = this->_graph1.sortedDeg[i - 1];
			}
			tmp = 1;
		}
	}
	ptr1++;
	this->_color = new bool[this->_graph1.vertexNumb];
	this->_bijection = new int[this->_graph1.vertexNumb];
	findDeg(deg, this->_graph1.vertexDeg, ptr1);
	cleanColor();
	this->_nullEdge = new fromTo;
	this->_lastEdge = this->_nullEdge;
	DFS(-1, ptr1);
	system("pause");
	for (int i = 0; i < this->_graph2.vertexNumb; i++)
		if (!this->_color[i])
			DFS(-1, i);
	cleanColor();
	cleanBijection();
	if (match(_nullEdge))
		return true;
	return false;
}

void CheckIsomorphism::findDeg(int deg, int * arr, int& ptr)
{
	if (ptr > this->_graph1.vertexNumb)
	{
		ptr = -1;
		return;
	}
	else
		while (arr[ptr] != deg) {
			ptr++;
			if (ptr > this->_graph1.vertexNumb)
			{
				ptr = -1;
				return;
			}
		}
}

bool CheckIsomorphism::match(fromTo* edge)
{

	if (edge->to == -1 || bSize == 0)
		return true;

	if (edge->from == -1 && _bijection[edge->to] == -1) {
		int ptr = 0;


		findDeg(this->_graph1.vertexDeg[edge->to], this->_graph2.vertexDeg, ptr);
		while (ptr != -1) {
			if (!_color[ptr])
			{
				_color[ptr] = true;
				_bijection[edge->to] = ptr;
				bSize--;
				if (match(edge->next))
					return true;
				_bijection[edge->to] = -1;
				bSize++;
				_color[ptr] = false;
			}
			ptr++;
			findDeg(this->_graph1.vertexDeg[edge->to], this->_graph2.vertexDeg, ptr);
		}
		return false;
	}
	if (edge->from == -1 && _bijection[edge->to] != -1)
		return match(edge->next);
	if (edge->from != -1 && _bijection[edge->to] == -1) {
		TNode* node = this->_graph2.adjList[_bijection[edge->from]];
		while (node) {
			if (!_color[node->numb]) {
				_color[node->numb] = true;
				bSize--;
				_bijection[edge->to] = node->numb;
				if (match(edge->next))
					return true;
				_bijection[edge->to] = -1;
				bSize++;
				_color[node->numb] = false;
				node = node->next;
			}
			else
				node = node->next;
		}
		return false;
	}
	if (edge->from != -1 && _bijection[edge->to] != -1) {
		TNode* node = this->_graph2.adjList[_bijection[edge->from]];
		while (node) {
			if (node->numb = _bijection[edge->to])
				return match(edge->next);
			node = node->next;
		}
	}
	return false;
}



void CheckIsomorphism::DFS(int from, int to)
{
	if (from == -1) {
		fromTo* tmp = new fromTo;
		_lastEdge->to = to;
		_lastEdge->next = tmp;
		//std::cout << _lastEdge->from << " " << _lastEdge->to << std::endl;
		_lastEdge = tmp;
		_color[to] = true;
		DFS(to, to);
	}
	else {
		TNode* node = this->_graph1.adjList[to];
		while (node) {
			fromTo* tmp = new fromTo;
			_lastEdge->from = from;
			_lastEdge->to = node->numb;
			_lastEdge->next = tmp;
			//std::cout << _lastEdge->from << " " << _lastEdge->to << std::endl;
			_lastEdge = tmp;
			if (!_color[node->numb]) {
				_color[node->numb] = true;
				DFS(node->numb, node->numb);
			}
			node = node->next;
		}
	}
}

void CheckIsomorphism::cleanColor()
{
	for (int i = 0; i < this->_graph1.vertexNumb; i++)
		this->_color[i] = false;
}

void CheckIsomorphism::cleanBijection()
{
	for (int i = 0; i < this->_graph1.vertexNumb; i++)
		this->_bijection[i] = -1;
	bSize = this->_graph1.vertexNumb;
}

void CheckIsomorphism::printBijection()
{

	for (int i = 0; i < this->_graph1.vertexNumb; i++)
		std::cout << i + 1 << " " << this->_bijection[i] + 1 << std::endl;
}
