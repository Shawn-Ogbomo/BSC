#include <iostream>
#include <fstream>
#include "reading.h"
void total_from_file(Reading& r, const std::string& file_name) {
	std::ifstream is{ file_name };
	if (!is) {
		std::cerr << "The file does not exist...\n";
		is.exceptions(is.exceptions() | std::ios_base::badbit);
		throw Reading::Invalid{};
	}
	for (int val{}; is >> val;) {
		r.sum += val;
		if (is.eof()) {
			return;
		}
	}
}