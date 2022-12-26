#include <iostream>
#include <vector>
#include "reading.h"
int main() {
	try {
		std::vector<Reading> temps;
		std::vector<Reading> temps_updated;
		fill_vector(temps);
		send_to_file(temps);
		fill_from_file(temps_updated, "raw_temps.txt");
		std::cout << "mean temp reading: " << mean(temps_updated) << "\n";
		std::cout << "median temp reading: " << median(temps_updated);
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << "\n";
		return 1;
	}
	catch (...) {
		std::cerr << "something went wrong...\nExiting...";
		return 2;
	}
}