#pragma once


//Data structure of linked list for possible strings on each position


struct Value
{
	char data;
	Value* next = nullptr;
	int numb = 0;
};



struct List {
public:
	List();
	~List();
	void push(char inputData);
	char next();
	void decrease();
	void del();
	unsigned size;
	Value *iterator;
	Value *begnode;
private:
	void findPush(char inputData, Value* node);
};