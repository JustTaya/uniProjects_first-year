#pragma once
#include "Linked_List.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>


struct TRule {
	std::string from = "";
	std::string to = "";
	bool term = false;
};

class MarkovAlgo {
private:
	std::fstream fin;
	LinkedList<TRule> rules;
public:
	MarkovAlgo();
	~MarkovAlgo();
	std::string work(std::string in);
};