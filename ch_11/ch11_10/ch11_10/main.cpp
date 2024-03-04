//Write a function vector<string> split(const string& s) that returns a vector
//of whitespace - separated substrings from the argument s

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

std::vector<std::string> split(const std::string& s) {
	if (!s.empty())
	{
		std::istringstream is{ s };
		std::vector<std::string> words;

		for (std::string internal_s; is >> internal_s;)
		{
			words.push_back(internal_s);
		}

		return words;
	}

	throw std::runtime_error{ "Oops something went wrong...\n" };
}

static void display_words(const std::vector<std::string>& words) {
	if (!words.empty())
	{
		std::cout << "\nresults: \n";

		for (const auto& word : words)
		{
			std::cout << word << "\n";
		}
	}
}

void check_stream(const std::istream& is = std::cin) {
	if (is.fail() || is.bad())
	{
		throw std::runtime_error{ "exiting...\n" };
	}
}

int main() {
	while (true) try
	{
		std::cout << "Please enter a string. Press ctrl+z to exit:  \n\n";

		std::string s;

		std::getline(std::cin, s);
		check_stream();
		display_words(split(s));

		std::cout << "\n";
	}

	catch (std::exception& e)
	{
		std::cerr << e.what();
		return 1;
	}
}