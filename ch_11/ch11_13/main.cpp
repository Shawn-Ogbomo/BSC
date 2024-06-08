//Reverse the order of words(defined as whitespace - separated strings) in a
//file.For example, Norwegian Blue parrot becomes parrot Blue Norwegian.
//You are allowed to assume that all the strings from the file will fit into
//memory at once

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main() {
	std::cout << "This program will read all the words in a file and produce a new file with the firsts files contents in reverse.\n Enter a file name: ";

	std::string filename;

	std::cin >> filename;

	std::ifstream ifs{ filename };

	if (!ifs)
	{
		std::cerr << "Sorry the file: " << filename << " does not exist...\n";
		ifs.clear(ifs.exceptions() | std::ios::badbit);
		return 1;
	}

	std::vector<std::string> words;

	for (std::string word; ifs >> word;)
	{
		words.push_back(word);
	}

	std::ofstream ofs{ "output.txt" };

	std::for_each(words.rbegin(), words.rend(), [&ofs](const std::string& word) {
		ofs << word << " ";
		});
}