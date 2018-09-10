#include "Graph.h"

/*INPUT
vertexNumb
neighbours of first vertex
...
...
neighbours of the vertexNumb vertex
*/


Graph::Graph(FILE * in)
{
	char buff = fgetc(in);
	while (buff != '\n') {
		if (buff == ' ') {
			buff = fgetc(in);
			continue;
		}
		vertexNumb *= 10;
		vertexNumb += buff - '0';
		buff = fgetc(in);
	}
	vertexDeg = new int[vertexNumb];
	sortedDeg = new int[vertexNumb];
	for (int i = 0; i < vertexNumb; i++) {
		vertexDeg[i] = 0;
		sortedDeg[i] = 0;
	}
	init(in);
	sortDeg();
}


void Graph::sortDeg()
{
	int j;
	int tmp;
	for (int k = vertexNumb / 2; k > 0; k /= 2)
		for (int i = k; i < vertexNumb; i++)
		{
			tmp = sortedDeg[i];
			for (j = i; j >= k; j -= k)
			{
				if (tmp < sortedDeg[j - k])
					sortedDeg[j] = sortedDeg[j - k];
				else
					break;
			}
			sortedDeg[j] = tmp;
		}
}

void Graph::init(FILE * in)
{
	char buff;
	int tmp = 0;
	adjList = new TNode*[vertexNumb];
	for (int i = 0; i < vertexNumb; i++)
		adjList[i] = nullptr;
	for (int i = 0; i < vertexNumb; i++) {
		buff = fgetc(in);
		while (buff == ' ')
			buff = fgetc(in);
		if (buff == '\n' || buff == EOF) {
			adjList[i] = nullptr;
			continue;
		}
		while (buff != '\n' && buff != EOF) {
			if (buff == ' ') {
				if (tmp != 0)
					push(tmp - 1, i);
				tmp = 0;
				buff = fgetc(in);
				continue;
			}
			tmp *= 10;
			tmp += buff - 48;
			buff = fgetc(in);
			if (tmp > vertexNumb)
			{
				std::cout << "ERROR. Invalid vertex numb.\n";
				system("pause");
				exit(EXIT_FAILURE);
			}
		}
		push(tmp - 1, i);
		tmp = 0;
	}

}

void Graph::push(int numb, int pos)
{
	TNode* tmp = new TNode;
	float k = log10(vertexNumb);
	int x = (int)k, y = 1;
	if (k > x)
		x++;
	for (int i = 0; i < x; i++)
		y *= 10;
	vertexDeg[numb] += y;
	vertexDeg[pos]++;
	sortedDeg[numb] = vertexDeg[numb];
	sortedDeg[pos] = vertexDeg[pos];
	tmp->numb = numb;
	tmp->next = adjList[pos];
	adjList[pos] = tmp;
}
