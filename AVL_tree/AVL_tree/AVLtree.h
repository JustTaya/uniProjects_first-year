#pragma once
#include <iostream>
#include "Stack.h"
#include "Queue.h"
#include <string>

//TODO
//helper functions

//int compare(const int&, const int&);
//int compare(const float&, const float&);
/*...*/

//void print(const int&, const std::string&);
//void print(const float&, const std::string&);
/*...*/

template <class TKey, class TValue>
class AVLTreeNode
{
public:
	AVLTreeNode(const TKey insertKey, const TValue inputValue) :_key(insertKey), _value(inputValue) {};
	int balanceFactor() const;
	void setHeight();
	template<class TKey, class TValue> friend class AVLTree;
private:
	TKey _key = 0;
	TValue _value = 0;
	int _heigh = 1;
	AVLTreeNode<TKey, TValue> *_left = nullptr;
	AVLTreeNode<TKey, TValue> *_right = nullptr;
};


template<class TKey, class TValue>
inline int AVLTreeNode<TKey, TValue>::balanceFactor() const
{
	if (!this)
		return 0;
	if (!_right) {
		if (this->_left)
			return 2;
		return 1;
	}
	if (!_left) {
		if (this->_right)
			return -2;
		return 1;
	}
	return _left->_heigh - _right->_heigh;
}

template<class TKey, class TValue>
inline void AVLTreeNode<TKey, TValue>::setHeight()
{
	if (!_right) {
		if (_left)
			_heigh = _left->_heigh;
		return;
	}
	else if (!_left) {
		if (_right)
			_heigh = _right->_heigh;
		return;
	}
	else
		_heigh = _left->_heigh > _right->_heigh ? _left->_heigh : _right->_heigh + 1;
}


template<class TKey, class TValue>
class AVLTree {
public:
	AVLTree() :_root(nullptr) {};
	~AVLTree();
	void push(TKey key, TValue value);

	//functions to print the tree
	void printLevels() const;     //uses the queue to print tree level by level
	void printPost() const;
	void printPre() const;
	void printIn() const;

	void del(TKey key);            //delete node with given key
private:
	AVLTreeNode<TKey, TValue>* _root;

	void deleteTree(AVLTreeNode<TKey, TValue>* tree);
	void insertNode(AVLTreeNode<TKey, TValue>* newNode);
	AVLTreeNode<TKey, TValue>* rec_insertNode(AVLTreeNode<TKey, TValue>* newNode, AVLTreeNode<TKey, TValue>* tree);

	void recDel(AVLTreeNode<TKey, TValue>* tree);
	AVLTreeNode<TKey, TValue>* recDel(AVLTreeNode<TKey, TValue>* tree, TKey key);
	AVLTreeNode<TKey, TValue>* findLeast(AVLTreeNode<TKey, TValue>* node);
	AVLTreeNode<TKey, TValue>* delLeast(AVLTreeNode<TKey, TValue>* node);
	AVLTreeNode<TKey, TValue>* balance(AVLTreeNode<TKey, TValue>* tree);
	AVLTreeNode<TKey, TValue>* rotateLeft(AVLTreeNode<TKey, TValue>* tree);
	AVLTreeNode<TKey, TValue>* rotateRight(AVLTreeNode<TKey, TValue>* tree);

	void printPostTree(const AVLTreeNode<TKey, TValue>* node) const;
	void printPreTree(const AVLTreeNode<TKey, TValue>* node) const;
	void printInTree(const AVLTreeNode<TKey, TValue>* node) const;
};

template<class TKey, class TValue>
AVLTree<TKey, TValue>::~AVLTree()
{
	if (this->_root)
		recDel(this->_root);
}

template<class TKey, class TValue>
inline void AVLTree<TKey, TValue>::push(TKey key, TValue value)
{
	AVLTreeNode<TKey, TValue>* newNode = new AVLTreeNode<TKey, TValue>(key, value);
	this->_root = rec_insertNode(newNode, this->_root);
}

template<class TKey, class TValue>
struct Level {
	int level = 0;
	AVLTreeNode<TKey, TValue>* node = nullptr;
};

template<class TKey, class TValue>
inline void AVLTree<TKey, TValue>::printLevels() const
{
	structures::Queue<Level< TKey, TValue>*> q;
	int l = 1;
	Level<TKey, TValue>* tmp = new Level<TKey, TValue>();
	tmp->level = 0;
	tmp->node = this->_root;
	q.enqueue(tmp);
	//cout << "level" << 0 << " ";
	while (!q.empty())
	{
		tmp = q.dequeue();
		if (l != tmp->level)
		{
			std::cout << std::endl;
			std::cout << "level" << tmp->level << " ";
			l = tmp->level;
		}
		std::cout << tmp->node->color << tmp->node->key << " ";
		if (tmp->node->left != nullptr) {
			Level<TKey, TValue>* left = new Level<TKey, TValue>();
			left->node = tmp->node->left;
			left->level = l + 1;
			q.enqueue(left);
		}
		if (tmp->node->right != nullptr) {
			Level<TKey, TValue>* right = new Level<TKey, TValue>();
			right->node = tmp->node->right;
			right->level = l + 1;
			q.enqueue(right);
		}
		delete tmp;
	}
}


template<class TKey, class TValue>
inline void AVLTree<TKey, TValue>::printPost() const
{
	printPostTree(this->_root);
}

template<class TKey, class TValue>
inline void AVLTree<TKey, TValue>::printPre() const
{
	printPreTree(this->_root);
}

template<class TKey, class TValue>
inline void AVLTree<TKey, TValue>::printIn() const
{
	printInTree(this->_root);
}


template<class TKey, class TValue>
void AVLTree<TKey, TValue>::deleteTree(AVLTreeNode<TKey, TValue>* tree)
{
	AVLTreeNode<TKey, TValue>* tmp = tree;
	Structures::Stack<AVLTreeNode<TKey, TValue>*> stack;
	stack.pushBack(tree);
	while (tree) {
		tmp = stack.popBack();
		if (!tmp)
			break;
		if (tmp->_left) {
			stack.pushBack(tmp);
			stack.pushBack(tmp->_left);
			continue;
		}
		else if (tmp->_right) {
			stack.pushBack(tmp);
			stack.pushBack(tmp->_right);
			continue;
		}
		else
			delete tmp;
	}
}

template<class TKey, class TValue>
void AVLTree<TKey, TValue>::insertNode(AVLTreeNode<TKey, TValue>* newNode)
{
	if (!this->_root)
	{
		this->_root = newNode;
		return;
	}
	AVLTreeNode<TKey, TValue>* tmp = this->_root;
	Structures::Stack<AVLTreeNode<TKey, TValue>*> stack;
	stack.pushBack(tmp);
	while (tmp) {
		tmp = stack.popBack();
		if (!newNode && tmp) {
			balance(tmp);
			continue;
		}
		if (!tmp)
			tmp = stack.popBack();
		else {
			if (tmp->_key > newNode->_key) {
				if (!tmp->_left) {
					tmp->_left = newNode;
					newNode = nullptr;
					continue;
				}
				stack.pushBack(tmp);
				stack.pushBack(tmp->_left);
				continue;
			}
			if (tmp->_key < newNode->_key) {
				if (!tmp->_right) {
					tmp->_left = newNode;
					newNode = nullptr;
					continue;
				}
				stack.pushBack(tmp);
				stack.pushBack(tmp->_right);
				continue;
			}
			if (tmp->_key == newNode->_key)
			{
				tmp->_value = newNode->_value;
				delete newNode;
				return;
			}
		}
	}
}

template<class TKey, class TValue>
inline AVLTreeNode<TKey, TValue>* AVLTree<TKey, TValue>::rec_insertNode(AVLTreeNode<TKey, TValue>* newNode, AVLTreeNode<TKey, TValue>* tree)
{
	if (!tree)
		return newNode;
	if (newNode->_key == tree->_key) {
		tree->_value = newNode->_value;
		delete newNode;
		return tree;
	}
	if (newNode->_key < tree->_key)
		tree->_left = rec_insertNode(newNode, tree->_left);
	else
		tree->_right = rec_insertNode(newNode, tree->_right);
	return balance(tree);
}




template<class TKey, class TValue>
inline void AVLTree<TKey, TValue>::recDel(AVLTreeNode<TKey, TValue> * tree)
{
	if (tree)
	{
		recDel(tree->_left);
		recDel(tree->_right);
		delete tree;
	}
}

template<class TKey, class TValue>
inline AVLTreeNode<TKey, TValue> * AVLTree<TKey, TValue>::recDel(AVLTreeNode<TKey, TValue>* tree, TKey key)
{
	if (!tree)
		return nullptr;
	if (key < tree->_key)
		tree->_left = recDel(tree->_left, key);
	else if (key > tree->_key)
		tree->_right = recDel(tree->_right, key);
	else {
		AVLTreeNode<TKey, TValue>* left = tree->_left;
		AVLTreeNode<TKey, TValue>* right = tree->_right;
		delete tree;
		if (!right)
			return left;
		AVLTreeNode<TKey, TValue>* min = findLeast(right);
		min->_right = delLeast(right);
		min->_left = left;
		return balance(min);
	}
}


template<class TKey, class TValue>
void AVLTree<TKey, TValue>::del(TKey key)
{
	if (!this->_root)
		return;
	this->_root = recDel(this->_root, key);
}

template<class TKey, class TValue>
inline AVLTreeNode<TKey, TValue> * AVLTree<TKey, TValue>::findLeast(AVLTreeNode<TKey, TValue> * node)
{
	while (node->_left)
		node = node->_left;
	return node;
}

template<class TKey, class TValue>
AVLTreeNode<TKey, TValue>* AVLTree<TKey, TValue>::delLeast(AVLTreeNode<TKey, TValue> * node)
{
	if (!node->_left)
		return node->_right;
	node->_left = delLeast(node->_left);
	return balance(node);
}

template<class TKey, class TValue>
AVLTreeNode<TKey, TValue> * AVLTree<TKey, TValue>::balance(AVLTreeNode<TKey, TValue> * tree)
{
	if (!tree)
		return nullptr;
	tree->setHeight();
	if (tree->balanceFactor() == 2) {
		if (tree->_right->balanceFactor() < 0)
			tree->_right = rotateRight(tree->_right);
		return rotateLeft(tree);
	}
	if (tree->balanceFactor() == -2) {
		if (tree->_left->balanceFactor() > 0)
			tree->_left = rotateLeft(tree->_left);
		return rotateRight(tree);
	}
	return tree;
}

template<class TKey, class TValue>
inline AVLTreeNode<TKey, TValue> * AVLTree<TKey, TValue>::rotateLeft(AVLTreeNode<TKey, TValue> * tree)
{
	AVLTreeNode<TKey, TValue>* tmp = tree->_left;
	tree->_left = tmp->_right;
	tmp->_right = tree;
	tmp->setHeight();
	tree->setHeight();
	return tmp;
}

template<class TKey, class TValue>
inline AVLTreeNode<TKey, TValue> * AVLTree<TKey, TValue>::rotateRight(AVLTreeNode<TKey, TValue> * tree)
{
	AVLTreeNode<TKey, TValue>* tmp = tree->_right;
	tree->_right = tmp->_left;
	tmp->_left = tree;
	tmp->setHeight();
	tree->setHeight();
	return tmp;
}



template<class TKey, class TValue>
inline void AVLTree<TKey, TValue>::printPostTree(const AVLTreeNode<TKey, TValue> * node) const
{
	if (node)
	{
		printPostTree(node->_left);
		printPostTree(node->_right);
		std::cout << node->_key << ' ' << node->_value << std::endl;
	}
	else
		return;
}


template<class TKey, class TValue>
inline void AVLTree<TKey, TValue>::printPreTree(const AVLTreeNode<TKey, TValue> * node) const
{
	if (node)
	{
		std::cout << node->_key << ' ' << node->_value << std::endl;
		printPreTree(node->_left);
		printPreTree(node->_right);
	}
	return;
}


template<class TKey, class TValue>
inline void AVLTree<TKey, TValue>::printInTree(const AVLTreeNode<TKey, TValue>* node) const
{
	if (node)
	{
		printInTree(node->_left);
		std::cout << node->_key << ' ' << node->_value << std::endl;
		printInTree(node->_right);
	}
	else
		return;
}
