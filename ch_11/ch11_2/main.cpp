#include <iostream>
#include <fstream>
#include <string>

using namespace std::string_literals;
//2.Write a program that given a file name and a word outputs each line that
//contains that word together with the line number.Hint: getline().

int main() {
	std::cout << "Please enter the name of your input file followed by the word you are searching for: ";

	auto file_name = ""s;
	auto word = ""s;

	std::cin >> file_name >> word;

	std::ifstream ifs{ file_name };

	if (!ifs) {
		std::cerr << "The file: " << file_name << "does not exist...\n";
		ifs.clear(ifs.exceptions() | std::ios::badbit);
		return 1;
	}

	for (auto line = ""s; std::getline(ifs, line);) {
		if (line.find(word) != std::string::npos) {
			std::cout << line << "\n";
		}
	}
}