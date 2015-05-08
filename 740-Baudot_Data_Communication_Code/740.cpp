#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#define BAUDOT_SIZE 	5

std::string processLine(std::vector<std::string> charSet, std::string line)
{
	std::string out = "";
	int shiftState = 0;

	for (int i = 0; i < line.length(); i+=BAUDOT_SIZE)
	{
		int charCode = std::stoi(line.substr(i, BAUDOT_SIZE), nullptr, 2);

		if (charCode == 31)
			shiftState = 1;
		else if (charCode == 27)
			shiftState = 0;
		else if (shiftState < charSet.size() && charCode < charSet[shiftState].length())
			out.append(charSet[shiftState].substr(charCode, 1));
	}

	return out;
}

int main(int argc, char** argv)
{
	std::vector<std::string> charSet;
	std::string line;

	for (int i=0;i<2;i++)
	{
		std::getline(std::cin, line);
		charSet.push_back(line);
	}

	while(std::getline(std::cin, line))
	{
		std::cout << processLine(charSet, line) << "\n";
	}
}