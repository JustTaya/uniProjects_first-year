#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Graph.h"
#include "CheckIsomorphism.h"

int main() {
	char fName[256];
	FILE* in = nullptr;
	while (!in) {
		std::cin >> fName;
		in = fopen(fName, "r");
	}
	rewind(in);
	Graph one(in);
	Graph two(in);
	CheckIsomorphism run(one, two);
	if (run.check()) {
		std::cout << "Y" << std::endl;
		run.printBijection();
	}
	else
		std::cout << "N" << std::endl;
	system("pause");
	return 0;
}