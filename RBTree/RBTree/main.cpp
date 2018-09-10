#include <iostream>
#include "RBTree.h"

using namespace std;

int one(int* matrix[10])
{
	return 0;
}

int main() {
	RBTree<int, int> tree;
	tree.insertKey(1, 1);
	tree.insertKey(6, 6);
	tree.insertKey(8, 8);
	tree.insertKey(11, 11);
	tree.insertKey(13, 13);
	tree.insertKey(15, 15);
	tree.insertKey(17, 17);
	tree.insertKey(22, 22);
	tree.insertKey(25, 25);
	tree.insertKey(27, 27);
	tree.printLevels();
	system("pause");
	return 0;
}

/*tree.insertKey(5,0);
tree.insertKey(2, 0);
tree.insertKey(9, 0);
tree.insertKey(1, 0);
tree.insertKey(6, 0);
tree.insertKey(8, 0);
tree.insertKey(0, 0);
tree.insertKey(20, 0);
tree.insertKey(30, 0);
tree.insertKey(35, 0);
tree.insertKey(40, 0);
tree.insertKey(50, 0);
tree.insertKey(0, 0);*/