#pragma once
#include "Graph.h"

struct fromTo {
	int from = -1;
	int to = -1;
	fromTo* next = nullptr;
};

class CheckIsomorphism
{
public:
	CheckIsomorphism(const Graph& graph1, const Graph& graph2) : _graph1(graph1), _graph2(graph2) {	};
	//~CheckIsomorphism();
	bool check();
	void printBijection();
private:
	Graph _graph1;      //etalon graph
	Graph _graph2;
	bool* _color;
	fromTo* _nullEdge = nullptr;
	fromTo* _lastEdge = nullptr;
	int* _bijection;
	int bSize;
	int ptr1 = -1;
	int ptr2 = -1;
	void findDeg(int deg, int* arr, int& ptr);
	bool match(fromTo* edge);
	void DFS(int from, int to);
	void cleanColor();
	void cleanBijection();
};

