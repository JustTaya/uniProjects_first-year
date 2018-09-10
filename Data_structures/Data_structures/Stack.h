#pragma once
#include <iostream>
#include "Structures.h"


namespace structures {
	template <class T>
	struct TNode_s
	{
		T data;
		TNode_s<T>* next = NULL;
	};
	template <class T>
	class Stack
	{
	public:
		Stack();
		~Stack();
		void pushBack(T input_data);
		void popBack();
		T top();
		bool empty();
		size_t size();
	private:
		TNode_s<T> *top_;
		size_t size_;
	};


	template<class T>
	Stack<T>::Stack()
	{

		this->top_ = nullptr;
		this->size_ = 0;
	}

	template<class T>
	Stack<T>::~Stack()
	{
		TNode_s<T> *tmp;
		while (this->top_) {
			tmp = this->top_;
			this->top_ = this->top_->next;
			delete tmp;
		}
		size_ = 0;
	}

	template<class T>
	void Stack<T>::pushBack(T inputData)
	{
		TNode_s<T>* node = new TNode_s<T>();
		node->data = inputData;
		node->next = this->top_;
		this->top_ = node;
		size_++;
	}

	template<class T>
	void Stack<T>::popBack()
	{
		TNode_s<T>* tmp = this->top_;
		this->top_ = this->top_->next;
		delete tmp;
		size_--;
	}


	template<class T>
	T Stack<T>::top()
	{
		return this->top_->data;
	}

	template<class T>
	bool Stack<T>::empty()
	{
		if (top_ == nullptr)
			return true;
		return false;
	}

	template<class T>
	size_t Stack<T>::size()
	{
		return size_;
	}

}