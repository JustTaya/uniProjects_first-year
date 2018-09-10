#pragma once 
#include <iostream>

namespace structures {
	template <class T>
	struct TNode_q
	{
		T data;
		TNode_q<T>* next = NULL;
	};
	template <class T>
	class Queue {
	public:
		Queue();
		~Queue();
		void enqueue(T  inputData);
		T dequeue();
		bool empty();
		size_t size();
	private:
		TNode_q<T> *head_;
		TNode_q<T> *tail_;
		size_t size_;
	};

	template<class T>
	inline Queue<T>::Queue()
	{
		head_ = nullptr;
		tail_ = head_;
		size_ = 0;
	}

	template<class T>
	Queue<T>::~Queue()
	{
		TNode_q<T>* tmp;
		while (this->head_) {
			tmp = this->head_;
			this->head_ = this->head_->next;
			delete tmp;
		}
	}

	template<class T>
	void Queue<T>::enqueue(T inputData)
	{
		TNode_q<T>* tmp = new TNode_q<T>();
		tmp->data = inputData;
		size_++;
		if (this->head_ == nullptr) {
			this->head_ = tmp;
			this->tail_ = tmp;
		}
		else {
			(this->tail_)->next = tmp;
			this->tail_ = tmp;
		}
	}

	template<class T>
	T Queue<T>::dequeue()
	{
		TNode_q<T>*tmp = this->head_;
		T outputData = this->head_->data;
		this->head_ = this->head_->next;
		size_--;
		delete tmp;
		return outputData;
	}

	template<class T>
	bool Queue<T>::empty()
	{
		if (this->head_ == nullptr)
			return true;
		return false;
	}

	template<class T>
	size_t Queue<T>::size()
	{
		return size_;
	}
}