#include <iostream>
#include <vector>
#include "reading.h"
int main() {
	try {
		std::vector<Reading> temps;
		fill_vector(temps);
		send_to_file(temps);
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << "\n";
		return 1;
	}
	catch (...) {
		std::cerr << "something went wrong...\n";
		return 2;
	}
}