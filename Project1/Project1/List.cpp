#include "List.h"
#include <iostream>


List::List()
{
	this->begnode = nullptr;
	this->iterator = nullptr;
	size = 0;
}


List::~List()
{
	Value* tmp;
	while (begnode) {
		size--;
		tmp = this->begnode;
		this->begnode = this->begnode->next;
		delete tmp;
	}
}

void List::push(char inputData)
{

	if (!size) {
		size++;
		this->begnode = new Value;
		this->begnode->data = inputData;
		this->begnode->numb++;
		this->iterator = this->begnode;
		return;
	}
	else if ((int)inputData < (int)(begnode->data)) {
		size++;
		Value* tmp = new Value;
		tmp->data = inputData;
		tmp->numb++;
		tmp->next = this->begnode;
		this->begnode = tmp;
		return;
	}
	else
		findPush(inputData, this->begnode);
}


char List::next()
{
	if (this->iterator->next)
		this->iterator = this->iterator->next;
	return (this->iterator->data);
}

void List::decrease()
{
	iterator->numb--;
	if (iterator->numb < 1)
		del();
}

void List::del()
{
	Value* tmp = iterator;
	iterator = begnode;
	while (iterator->next != tmp)
		iterator = iterator->next;
	iterator = iterator->next->next;
	delete tmp;
}

void List::findPush(char inputData, Value * node)
{
	if (inputData == node->data) {
		node->numb++;
		return;
	}
	else if ((int)inputData > (int)node->data && node->next == nullptr) {
		Value *tmp = new Value;
		tmp->data = inputData;
		node->next = tmp;
		tmp->numb++;
		size++;
	}
	else if ((int)inputData > (int)node->data && (int)inputData < (int)node->next->data) {
		Value *tmp = new Value;
		tmp->data = inputData;
		tmp->next = node->next;
		node->next = tmp;
		node->numb++;
		size++;
	}
	else
		findPush(inputData, node->next);
}