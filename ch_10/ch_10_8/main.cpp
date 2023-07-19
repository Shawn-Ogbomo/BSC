#include <iostream>
#include <string>
#include <fstream>

//Write a program that accepts two file names and produces a new file
//that is the contents of the first file followed by the contents of the second;
//that is, the program concatenates the two files.

void greeting() {
	static auto call_count = 0;
	++call_count;
	std::cout << "Please enter file name" << "(" << call_count << "): ";
}

void concatenate_files() {
	greeting();
	std::string file_name;
	std::cin >> file_name;
	std::ifstream ist{ file_name };

	if (!ist) {
		std::cerr << "The file: " << file_name << " does not exist...\n";
		ist.exceptions(ist.exceptions() | std::ios_base::badbit);
		return;
	}

	greeting();
	std::string file_name2;
	std::cin >> file_name2;
	std::ifstream ist2{ file_name2 };

	if (!ist2) {
		std::cerr << "The file: " << file_name2 << " does not exist...\n";
		ist.exceptions(ist2.exceptions() | std::ios_base::badbit);
		return;
	}
	std::ofstream ost{ "output.txt" };

	ost << ist.rdbuf();
	ost << ist2.rdbuf();
}

int main() {
	concatenate_files();
}