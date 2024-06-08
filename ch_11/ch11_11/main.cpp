//Write a function vector<string> split(const string& s, const string& w)
//that returns a vector of whitespace - separated substrings from the argument s, where whitespace is defined as “ordinary whitespace” plus the
//characters in w.

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include "exceptions.h"

bool find_duplicates(std::string_view target_string)
{
	return std::any_of(target_string.begin(), target_string.end(), [target_string](const char& c) {
		return  (std::count(target_string.begin(), target_string.end(), c) > 1);
		});
}

void check_stream(const std::istream& is = std::cin)
{
	if (is.fail())
	{
		throw Terminate{ "exiting..." };
	}
}

std::vector<std::string> split(const std::string& s, const std::string& w)
{
	std::string s_cpy = s;

	std::replace_if(s_cpy.begin(), s_cpy.end(), [&w](char c)
		{
			return w.find(c) != std::string::npos;
		}, ' ');

	std::istringstream iss{ s_cpy };

	std::vector<std::string> words;

	for (std::string word; iss >> word;)
	{
		words.push_back(word);
	}

	return words;
}

void display(const std::vector<std::string>& words) {
	std::cout << "results\n\n";

	std::for_each(words.begin(), words.end(), [](const std::string& word)
		{
			std::cout << word << "\n";
		});
}

int main() {
	while (true) try
	{
		std::cout << "Enter a string, then enter a set of characters you want to treat as whitespace. Press ctrl+z to exit:  ";

		std::string line;
		std::getline(std::cin, line);
		check_stream();

		std::cout << "\n\nEnter the characters that you want treated as whitespace\n";

		std::string white;
		std::getline(std::cin, white);
		check_stream();

		if (find_duplicates(white))
		{
			std::cerr << "Try again\n\n";
		}

		else
		{
			display(split(line, white));
			std::cout << "\n";
		}
	}
	catch (Terminate& e) {
		std::cerr << e.what();
		return 1;
	}
}