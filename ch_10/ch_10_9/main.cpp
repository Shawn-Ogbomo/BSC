#include <iostream>
#include <fstream>
#include <string>

//Write a program that takes two files containing sorted whitespace - separated words and merges them, preserving order.
void greeting() {
	static auto call_count = 0;
	++call_count;
	std::cout << "Please enter file name" << "(" << call_count << "): ";
}

void merge_files() {
	greeting();
	std::string file_name;
	std::cin >> file_name;
	std::fstream ost{ file_name, std::ios_base::out | std::ios::app };

	if (!ost) {
		std::cerr << "The file: " << file_name << " does not exist...\n";
		ost.exceptions(ost.exceptions() | std::ios_base::badbit);
		return;
	}

	greeting();
	std::string file_name2;
	std::cin >> file_name2;
	std::ifstream ist2{ file_name2 };

	if (!ist2) {
		std::cerr << "The file: " << file_name2 << " does not exist...\n";
		ist2.exceptions(ist2.exceptions() | std::ios_base::badbit);
		return;
	}

	for (std::string s; std::getline(ist2, s);) {
		ost << s << "\n";
	}
}

int main() {
	merge_files();
}