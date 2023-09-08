#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std::string_literals;
//1. Write a program that reads a text file and converts its input to all lower
//case, producing a new file

int main() {
	std::cout << "Please enter the name of your input file: ";

	auto file_name = ""s;
	std::cin >> file_name;

	std::ifstream ifs{ file_name };

	if (!ifs) {
		std::cerr << "The file: " << file_name << "does not exist...\n";
		ifs.clear(ifs.exceptions() | std::ios::badbit);
	}

	std::ofstream ofs{ "output.txt" };

	for (char c{}; ifs.get(c);) {
		if (std::isupper(c)) {
			c = std::tolower(c);
		}

		ofs << c;
	}
}