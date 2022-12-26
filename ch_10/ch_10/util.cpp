#include <iostream>
#include "util.h"
void Utils::skip_to_int(char term, std::istream& is) {
	if (is.bad()) {
		is.exceptions(is.exceptions() | std::ios_base::badbit);
		return;
	}
	if (is.eof()) {
		throw Invalid{};
	}
	if (is.fail()) {
		is.clear();
		for (char ch; std::cin >> ch;) {
			if (isdigit(ch) || ch == term) {
				std::cin.unget();
				return;
			}
		}
		is.clear(std::ios_base::failbit);
	}
}