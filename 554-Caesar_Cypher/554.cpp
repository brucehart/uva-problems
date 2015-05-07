#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <iterator>

#define  CHAR_SPACE 	" ABCDEFGHIJKLMNOPQRSTUVWXYZ"

std::vector<std::string> split(std::string s)
{
	std::stringstream ss(s);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> vstrings(begin, end);

	return vstrings;
}

int dictCount(std::unordered_set<std::string> dict, std::string text)
{
	int count = 0;
	std::vector<std::string> words = split(text);

	for(std::string w: words)
	{
		auto match = dict.find(w);

		if (match != dict.end())
			count++;
	}

	return count;
}

std::string reverse_caesar(std::unordered_set<std::string> dict, std::string cypherText)
{	
	int maxMatch = 0;
	std::string bestResult = cypherText;

	std::string charSpace = std::string(CHAR_SPACE);

	for (int i=1;i<charSpace.length();i++)
	{
		std::string testText = cypherText;

		std::for_each(testText.begin(), testText.end(), 
			[=](char& w){ 
				int x = 0; 
				if (w != ' ') x = (w - 'A' + 1);  
				x = ((x+i)%27); 
				w = charSpace[x];
			});		
		
		int matchCount = dictCount(dict, testText);

		if (matchCount > maxMatch)
		{
			bestResult = testText;
			maxMatch = matchCount;
		}
	}

	return bestResult;

}

std::string format_output(std::string txt, int n)
{
	int counter = 0;
	std::vector<std::string> words = split(txt);
	std::string out = "";

	for (int i=0;i<words.size();i++)
	{
		if ((words[i].length() + counter) > n)
		{
			out.append("\n");
			counter = 0;
		}
		else if (i > 0) 
		{
			out.append(" ");
			counter += 1;
		}

		out.append(words[i]);
		counter += words[i].length();
	}

	return out;
}

int main(int argc, char** argv)
{
	std::unordered_set<std::string> dict;
	std::string elem;
	std::string cypherText;

	while(std::getline(std::cin, elem))
	{
		if (elem.compare("#") == 0)
			break;

		dict.emplace(elem);		
	}

	std::getline(std::cin, cypherText);	
	std::string result = reverse_caesar(dict, cypherText);

	std::cout << format_output(result, 60) << "\n";	
}