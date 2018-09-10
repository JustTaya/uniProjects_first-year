#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <math.h>

struct TNode {
	int numb;
	TNode* next = nullptr;
};

class Graph
{
public:
	Graph(FILE* in);
	//	~Graph();
	int vertexNumb = 0;
	int* vertexDeg;
	int* sortedDeg;
	TNode * * adjList = nullptr;          //structure to represent a graph
private:
	void sortDeg();
	void init(FILE* in);
	void push(int numb, int pos);
};

