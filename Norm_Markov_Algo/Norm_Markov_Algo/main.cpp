#include "Markov_Algo.h"

int main() {
	std::cout << "Enter the file name.\n";  //file name with rules for algo
	MarkovAlgo one;
	std::string in;
	std::cout << "Enter the sample text.\n";
	std::getline(std::cin, in);
	one.work(in);
	system("pause");
	return 0;
}