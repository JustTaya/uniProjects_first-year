#include "Structures.h"
#include <iostream>
using namespace std;

int main() {
	structures::Queue<int>  A;
	A.enqueue(1);
	A.enqueue(2);
	cout << A.dequeue();
	cout << A.dequeue();
	system("pause");
	return 0;
}