#include <iostream>
#include "AVLtree.h"

using namespace std;

int main() {
	AVLTree<int, int> one;
	int n, tmpKey, tmpValue;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> tmpKey;
		if (tmpKey < 0)
			one.del(abs(tmpKey));
		else {
			cin >> tmpValue;
			one.push(tmpKey, tmpValue);
		}
	}
	one.printPre();
	system("pause");
	return 0;
}