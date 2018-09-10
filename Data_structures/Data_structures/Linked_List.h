#pragma once
#include <iostream>

namespace structures {
	template <class T>
	struct TNode_l
	{
		T data;
		TNode_l<T>* next = nullptr;
	};

	template <class T>
	class LinkedList {
	public:
		TNode_l<T> *it = nullptr;
		LinkedList();
		~LinkedList();
		bool setIterator(size_t position);
		T returnVal();
		bool pushBack(T inputData);
		bool insert(size_t position, T inputData);
		bool delElement(size_t position);
		size_t numb();
		TNode_l<T>* end();
	private:
		TNode_l<T> *begnode = nullptr;
		TNode_l<T> *headnode = nullptr;
		bool empty;
	};

	template<class T>
	LinkedList<T>::LinkedList()
	{
		this->begnode = nullptr;
		this->headnode = this->begnode;
		empty = true;
		this->it = this->begnode;
	}

	template<class T>
	LinkedList<T>::~LinkedList()
	{
		TNode_l<T>*node;
		while (begnode != nullptr) {
			node = this->begnode;
			this->begnode = (this->begnode)->next;
			delete (node);
		}
	}

	template<class T>
	bool LinkedList<T>::setIterator(size_t position)
	{
		this->it = this->begnode;
		for (size_t i = 0; i < position - 1; i++)
			this->it = (this->it)->next;
		return false;
	}

	template<class T>
	T LinkedList<T>::returnVal()
	{
		TNode_l<T> *node = this->it;
		this->it = it->next;
		return T(node->data);
	}

	template<class T>
	bool LinkedList<T>::pushBack(T inputData)
	{
		TNode_l<T>* tmp = new TNode_l<T>();
		tmp->data = inputData;
		if (empty) {
			empty = false;
			this->begnode = tmp;
			this->headnode = tmp;
			this->it = tmp;
			return false;
		}
		(this->headnode)->next = tmp;
		this->headnode = tmp;
		return false;
	}

	template<class T>
	bool LinkedList<T>::insert(size_t position, T inputData)
	{
		TNode_l<T>*node = new TNode_l<T>();
		node->data = inputData;
		if (position == 1) {
			node->next = this->begnode;
			begnode = node;
			return true;
		}
		else {
			TNode_l<T>* tmp = this->begnode;
			for (size_t i = 0; i < position - 2 && tmp->next; i++)
				tmp = tmp->next;
			node->next = tmp->next;
			tmp->next = node;
			if (node->next == nullptr)
				this->headnode = node;
			return true;
		}
		return false;
	}

	template<class T>
	bool LinkedList<T>::delElement(size_t position)
	{
		TNode_l<T>*tmp = this->begnode;
		if (position == 1) {
			this->begnode = (this->begnode)->next;
			delete tmp;
			return true;
		}
		else {
			for (size_t i = 0; i < position - 2; i++) {
				if (tmp->next == nullptr)
					return false;
				tmp = tmp->next;
			}
			TNode_l<T>*del = tmp->next;
			tmp->next = (tmp->next)->next;
			delete del;
			if (tmp->next == nullptr)
				this->headnode = tmp;
			return true;
		}
		return false;
	}

	template<class T>
	size_t LinkedList<T>::numb()
	{
		TNode_l<T>* tmp = this->begnode;
		size_t k = 1;
		while (tmp != this->headnode)
		{
			k++;
			tmp = tmp->next;
		}
		return k;
	}

	template<class T>
	TNode_l<T>* LinkedList<T>::end()
	{
		return (this->headnode);
	}
}