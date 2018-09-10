#pragma once
#include "Queue.h"
#define BLACK 0
#define RED 1
#define DOUBLE_BLACK 2

template <class TKey, class TData>
class TNode {
public:
	TNode<TKey, TData> * grandparent();
	TNode<TKey, TData>* uncle();
	TKey key;
	TData data;
	int color = RED;
	TNode<TKey, TData>* left = nullptr;
	TNode<TKey, TData>* right = nullptr;
	TNode<TKey, TData>* parent = nullptr;
};

template<class TKey, class TData>
inline TNode<TKey, TData> * TNode<TKey, TData>::grandparent()
{
	if (this && this->parent)
		return this->parent->parent;
	return nullptr;
}

template<class TKey, class TData>
TNode<TKey, TData> * TNode<TKey, TData>::uncle()
{
	TNode<TKey, TData>* tmp = this->grandparent();
	if (tmp != nullptr)
		if (this->parent == tmp->left)
			return tmp->right;
		else
			return tmp->left;
	return nullptr;
}

template<class TKey, class TData>
class RBTree {
public:
	RBTree() :_root(nullptr) {};
	~RBTree();

	//functions to print the tree
	void printLevels() const;     //uses the queue to print tree level by level
	void printPost() const;
	void printPre() const;
	void printIn() const;

	TData search(TKey key);

	void insertKey(TKey key, TData data);
	void deleteKey(TKey key);
private:
	TNode<TKey, TData> * _root = nullptr;

	TData searchKey(TKey key, TNode<TKey, TData>* node);

	void printPostTree(const TNode<TKey, TData>* node) const;
	void printPreTree(const TNode<TKey, TData>* node) const;
	void printInTree(const TNode<TKey, TData>* node) const;

	void deleteTree(TNode<TKey, TData>*node);

	int getColor(TNode<TKey, TData>*node);
	void setColor(TNode<TKey, TData>*node, int color);
	TNode<TKey, TData>* insertRBTree(TNode<TKey, TData>* node, TNode<TKey, TData>* ptr);
	TNode<TKey, TData>* deleteRBTree(TNode<TKey, TData>* node, TKey key);

	void fixInsertTree(TNode<TKey, TData>* node);
	void fixDeleteTree(TNode<TKey, TData>* node);
	void rotateLeft(TNode<TKey, TData>* node);
	void rotateRight(TNode<TKey, TData>* node);

	TNode<TKey, TData>* minKeyNode(TNode<TKey, TData>* node);
	TNode<TKey, TData>* maxKeyNode(TNode<TKey, TData>* node);
};

template<class TKey, class TValue>
inline void RBTree<TKey, TValue>::printPostTree(const TNode<TKey, TValue> * node) const
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
inline void RBTree<TKey, TValue>::printPreTree(const TNode<TKey, TValue> * node) const
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
inline void RBTree<TKey, TValue>::printInTree(const TNode<TKey, TValue>* node) const
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


template<class TKey, class TData>
RBTree<TKey, TData>::~RBTree()
{
	deleteTree(this->_root);
}

template<class TKey, class TData>
struct Level {
	int level = 0;
	TNode<TKey, TData>* node = nullptr;
};

template<class TKey, class TValue>
inline void RBTree<TKey, TValue>::printLevels() const
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
inline void RBTree<TKey, TValue>::printPost() const
{
	printPostTree(this->_root);
}

template<class TKey, class TValue>
inline void RBTree<TKey, TValue>::printPre() const
{
	printPreTree(this->_root);
}

template<class TKey, class TValue>
inline void RBTree<TKey, TValue>::printIn() const
{
	printInTree(this->_root);
}


template<class TKey, class TData>
inline TData RBTree<TKey, TData>::search(TKey key)
{
	return searchKey(key, this->_root);
}

template<class TKey, class TData>
inline TData RBTree<TKey, TData>::searchKey(TKey key, TNode<TKey, TData>* node)
{
	if (node == nullptr)
		return TData();
	if (node->key == key)
		return node->data;
	if (node->key > key)
		searchKey(key, node->left);
	if (node->key < key)
		searchKey(key, node->right);
	return TData();
}

template<class TKey, class TData>
void RBTree<TKey, TData>::deleteTree(TNode<TKey, TData>* node)
{
	if (node->left != nullptr)
		deleteTree(node->left);
	if (node->right != nullptr)
		deleteTree(node->right);
	delete node;
}

template<class TKey, class TData>
int RBTree<TKey, TData>::getColor(TNode<TKey, TData>* node)
{
	if (node == nullptr)
		return BLACK;
	return node->color;
}

template<class TKey, class TData>
void RBTree<TKey, TData>::setColor(TNode<TKey, TData>* node, int color)
{
	if (node == nullptr)
		return;
	node->color = color;
}

template<class TKey, class TData>
void  RBTree<TKey, TData>::insertKey(TKey key, TData data)
{
	TNode<TKey, TData>* node = new TNode<TKey, TData>();
	node->key = key; node->data = data;
	this->_root = insertRBTree(this->_root, node);
	fixInsertTree(node);
}

template<class TKey, class TData>
inline void RBTree<TKey, TData>::deleteKey(TKey key)
{
	TNode<TKey, TData>* node = deleteRBTree(this->_root, key);
	fixDeleteTree(node);
}

template<class TKey, class TData>
inline TNode<TKey, TData> * RBTree<TKey, TData>::insertRBTree(TNode<TKey, TData>* node, TNode<TKey, TData>* ptr)
{
	if (node == nullptr)
		return ptr;
	if (ptr->key < node->key) {
		node->left = insertRBTree(node->left, ptr);
		node->left->parent = node;
	}
	else if (ptr->key > node->key) {
		node->right = insertRBTree(node->right, ptr);
		node->right->parent = node;
	}
	return node;
}

template<class TKey, class TData>
inline TNode<TKey, TData>* RBTree<TKey, TData>::deleteRBTree(TNode<TKey, TData>* node, TKey key)
{
	if (node == nullptr)
		return node;
	if (key < node->key)
		return deleteRBTree(node->left, key);
	if (key > node->data)
		return deleteRBTree(node->right, key);
	if (node->left == nullptr || node->right == nullptr)
		return node;
	TNode<TKey, TData>* temp = minKeyNode(node->right);
	node->data = temp->key;
	return deleteRBTree(node->right, temp->data);
}

template<class TKey, class TData>
void RBTree<TKey, TData>::fixInsertTree(TNode<TKey, TData>* node)
{
	TNode<TKey, TData> *parent = nullptr;
	TNode<TKey, TData> *grandparent = nullptr;
	while (node != this->_root && getColor(node) == RED && getColor(node->parent) == RED) {
		parent = node->parent;
		grandparent = parent->parent;
		if (parent == grandparent->left) {
			TNode<TKey, TData> *uncle = grandparent->right;
			if (getColor(uncle) == RED) {
				setColor(uncle, BLACK);
				setColor(parent, BLACK);
				setColor(grandparent, RED);
				node = grandparent;
			}
			else {
				if (node == parent->right) {
					rotateLeft(parent);
					node = parent;
					parent = node->parent;
				}
				rotateRight(grandparent);
				int c = parent->color;
				parent->color = grandparent->color;
				grandparent->color = c;
				node = parent;
			}
		}
		else {
			TNode<TKey, TData> *uncle = grandparent->left;
			if (getColor(uncle) == RED) {
				setColor(uncle, BLACK);
				setColor(parent, BLACK);
				setColor(grandparent, RED);
				node = grandparent;
			}
			else {
				if (node == parent->left) {
					rotateRight(parent);
					node = parent;
					parent = node->parent;
				}
				rotateLeft(grandparent);
				int c = parent->color;
				parent->color = grandparent->color;
				grandparent->color = c;
				node = parent;
			}
		}
	}
	setColor(this->_root, BLACK);
}

template<class TKey, class TData>
void RBTree<TKey, TData>::fixDeleteTree(TNode<TKey, TData>* node)
{
	if (node == nullptr)
		return;
	if (node == this->_root) {
		this->_root = nullptr;
		return;
	}
	if (getColor(node) == RED || getColor(node->left) == RED || getColor(node->right) == RED) {
		TNode<TKey, TData> *child = node->left != nullptr ? node->left : node->right;

		if (node == node->parent->left) {
			node->parent->left = child;
			if (child != nullptr)
				child->parent = node->parent;
			setColor(child, BLACK);
			delete (node);
		}
		else {
			node->parent->right = child;
			if (child != nullptr)
				child->parent = node->parent;
			setColor(child, BLACK);
			delete (node);
		}
	}
	else {
		TNode<TKey, TData> *sibling = nullptr;
		TNode<TKey, TData> *parent = nullptr;
		TNode<TKey, TData> *ptr = node;
		setColor(ptr, DOUBLE_BLACK);
		while (ptr != this->_root && getColor(ptr) == DOUBLE_BLACK) {
			parent = ptr->parent;
			if (ptr == parent->left) {
				sibling = parent->right;
				if (getColor(sibling) == RED) {
					setColor(sibling, BLACK);
					setColor(parent, RED);
					rotateLeft(parent);
				}
				else {
					if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
						setColor(sibling, RED);
						if (getColor(parent) == RED)
							setColor(parent, BLACK);
						else
							setColor(parent, DOUBLE_BLACK);
						ptr = parent;
					}
					else {
						if (getColor(sibling->right) == BLACK) {
							setColor(sibling->left, BLACK);
							setColor(sibling, RED);
							rotateRight(sibling);
							sibling = parent->right;
						}
						setColor(sibling, parent->color);
						setColor(parent, BLACK);
						setColor(sibling->right, BLACK);
						rotateLeft(parent);
						break;
					}
				}
			}
			else {
				sibling = parent->left;
				if (getColor(sibling) == RED) {
					setColor(sibling, BLACK);
					setColor(parent, RED);
					rotateRight(parent);
				}
				else {
					if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
						setColor(sibling, RED);
						if (getColor(parent) == RED)
							setColor(parent, BLACK);
						else
							setColor(parent, DOUBLE_BLACK);
						ptr = parent;
					}
					else {
						if (getColor(sibling->left) == BLACK) {
							setColor(sibling->right, BLACK);
							setColor(sibling, RED);
							rotateLeft(sibling);
							sibling = parent->left;
						}
						setColor(sibling, parent->color);
						setColor(parent, BLACK);
						setColor(sibling->left, BLACK);
						rotateRight(parent);
						break;
					}
				}
			}
		}
		if (node == node->parent->left)
			node->parent->left = nullptr;
		else
			node->parent->right = nullptr;
		delete(node);
		setColor(this->_root, BLACK);
	}
}

template<class TKey, class TData>
void RBTree<TKey, TData>::rotateLeft(TNode<TKey, TData>* node)
{
	TNode<TKey, TData>*rightChild = node->right;
	node->right = rightChild->left;
	if (node->right != nullptr)
		node->right->parent = node;
	rightChild->parent = node->parent;
	if (node->parent == nullptr)
		this->_root = rightChild;
	else if (node == node->parent->left)
		node->parent->left = rightChild;
	else
		node->parent->right = rightChild;
	rightChild->left = node;
	node->parent = rightChild;
}

template<class TKey, class TData>
void RBTree<TKey, TData>::rotateRight(TNode<TKey, TData>* node)
{
	TNode<TKey, TData> *leftChild = node->left;
	node->left = leftChild->right;
	if (node->left != nullptr)
		node->left->parent = node;
	leftChild->parent = node->parent;
	if (node->parent == nullptr)
		this->_root = leftChild;
	else if (node == node->parent->left)
		node->parent->left = leftChild;
	else
		node->parent->right = leftChild;
	leftChild->right = node;
	node->parent = leftChild;
}

template<class TKey, class TData>
inline TNode<TKey, TData>* RBTree<TKey, TData>::minKeyNode(TNode<TKey, TData>* node)
{
	TNode<TKey, TData>*ptr = node;
	while (ptr->left != nullptr)
		ptr = ptr->left;
	return ptr;
}

template<class TKey, class TData>
inline TNode<TKey, TData>* RBTree<TKey, TData>::maxKeyNode(TNode<TKey, TData>* node)
{
	TNode<TKey, TData>*ptr = node;
	while (ptr->right != nullptr)
		ptr = ptr->right;
	return ptr;
}

