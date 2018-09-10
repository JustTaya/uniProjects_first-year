#include "Markov_Algo.h"

MarkovAlgo::MarkovAlgo()
{
	std::string fname;
	std::getline(std::cin, fname);
	std::ifstream fin(fname);
	TRule tmp;
	std::string buff = "";
	std::stringstream ss;
	bool flag = false;

	if (!fin.is_open())
		std::ifstream fin("1.txt");       //if name of file is incorrect open default file

	while (std::getline(fin, buff)) {

		if (buff[0] == '#')               //skip comments
			continue;
		ss << buff;

		while (!ss.eof()) {
			ss >> buff;

			if (buff == "->") {
				flag = true;
				continue;
			}

			if (!flag) {
				if (tmp.from != "")
					(tmp.from).push_back(' ');
				tmp.from.append(buff);
			}

			else {
				if (buff[0] == '*')        //terminate rules
				{
					tmp.term = true;
					buff.erase(0, 1);
				}

				if (tmp.to != "")
					(tmp.to).push_back(' ');
				tmp.to.append(buff);
			}
		}
		rules.pushBack(tmp);
		flag = false;
		tmp.from = ""; tmp.to = ""; tmp.term = false; ss.clear();
	}
}

MarkovAlgo::~MarkovAlgo()
{
	fin.close();
}

std::string MarkovAlgo::work(std::string in)
{
	std::string out = in;
	size_t n = rules.numb();
	TRule tmp;
	rules.setIterator(1);

	for (size_t i = 0; i < n; i++) {
		tmp = rules.returnVal();
		size_t pos = out.find(tmp.from, 0);

		if (pos != std::string::npos) {
			out.replace(pos, tmp.from.length(), tmp.to);
			if (!tmp.term && out != in)                    //finish if terminate rule or no changes
			{
				std::cout << out << '\n';
				return work(out);
			}
			else return out;
		}
	}
	std::cout << out << '\n';
	return out;
}