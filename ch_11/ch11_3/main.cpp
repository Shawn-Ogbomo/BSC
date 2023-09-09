#include <iostream>
#include <fstream>
#include <string>

using namespace std::string_literals;
//3. Write a program that removes all vowels from a file (“disemvowels”). For
//example, Once upon a time!becomes nc pn tm!.Surprisingly often, the
//result is still readable; try it on your friends.

int main() {
	std::cout << "Please enter the name of your input file: ";

	auto file_name = ""s;

	std::cin >> file_name;

	std::ifstream ifs{ file_name };

	if (!ifs) {
		std::cerr << "The file: " << file_name << "does not exist...\n";
		ifs.clear(ifs.exceptions() | std::ios::badbit);
		return 1;
	}

	std::ofstream os{ "output.txt" };

	for (char c{}; ifs.get(c);) {
		switch (c = std::tolower(c)) {
		case'a':
		case'e':
		case'i':
		case'o':
		case'u': {
			c = {};
			os << c;
			break;
		}
		default:
			os << c;
			break;
		}
	}
}