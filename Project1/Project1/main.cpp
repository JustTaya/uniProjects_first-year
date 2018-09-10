#pragma warning(disable : 4996)
#include <iostream>
#include "Sort.h"

using namespace std;

int main() {
	int n;
	cin >> n;
	char**in = new char*[n];
	for (int i = 0; i < n; i++) {
		in[i] = new char[512];
		cin >> in[i];
	}
	system("cls");
	in = BucketSort(in, n, 0);
	for (int i = 0; i < n; i++) {
		cout << in[i] << endl;
	}
	system("pause");
	return 0;
}