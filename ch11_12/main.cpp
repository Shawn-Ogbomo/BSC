//Reverse the order of characters in a text file.For example, asdfghjkl becomes lkjhgfdsa.
//Warning: There is no really good, portable, and efficient
//way of reading a file backward

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

void check_stream(std::istream& is, const std::string& message) {
	if (std::cin.eof())
	{
		throw std::runtime_error{ "exiting...\n" };
	}

	if (is.fail())
	{
		is.clear(is.exceptions() | std::ios::badbit);
		throw std::runtime_error{ message };
	}
}
int main() {
	try {
		std::cout << "Please enter a file name. Press ctrl+z to exit:  ";

		std::string file_name;
		std::cin >> file_name;

		std::ifstream ifs{ file_name };
		check_stream(ifs, "Sorry the file " + std::string{ file_name } + " does not exist...\n");

		std::string letters;

		for (char c{}; ifs.get(c);)
		{
			letters += c;
		}

		std::ofstream ofs{ "output.txt" };

		std::for_each(letters.rbegin(), letters.rend(), [&ofs](const auto& c) {
			ofs << c;
			});
	}

	catch (std::exception& e)
	{
		std::cerr << e.what();
		return 1;
	}
}