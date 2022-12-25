#include <iostream>
#include <fstream>
#include <stdexcept>
#include "reading.h"
int main() {
	try {
		Reading r;
		std::string f_name{};
		std::cout << "Please enter the name of the file: ";
		std::cin >> f_name;
		total_from_file(r, f_name);
		std::cout << "Total: " << r.sum;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << "\n";
	}
	catch (...) {
		std::cerr << "exiting...\n";
	}
}