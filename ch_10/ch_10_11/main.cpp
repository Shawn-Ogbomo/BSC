#include <iostream>
#include <fstream>
//Write a program that produces the sum of all the whitespace - separated integers in a text file.For example, bears: 17 elephants 9 end should output 26.

int main() {
	std::cout << "Please enter file name: ";
	std::string file_name;
	std::cin >> file_name;
	std::ifstream ist{ file_name };

	if (!ist) {
		std::cerr << "The file: " << file_name << " does not exist...\nExiting...";
		return 1;
	}

	auto total = 0;

	while (ist) {
		char c{};

		while (ist.get(c) && (!isdigit(c)));

		ist.unget();

		auto num = 0;

		ist >> num;
		total += num;
	}

	std::cout << "The sum of all numbers in the file is: " << total << "\n";
}