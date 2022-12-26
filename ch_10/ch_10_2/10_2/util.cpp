#include <iostream>
#include "util.h"
int Utils::get_int(std::istream& is) {
	int n = 0;
	while (true) {
		if (is >> n) {
			return n;
		}
		std::cout << "Sorry that was not a number; please try again\n";
		skip_to_int();
	}
}

int Utils::get_int(int low, int high, const std::string& greeting, const std::string& sorry) {
	std::cout << greeting << ":[" << low << ':' << high << "]\n";
	while (true) {
		int n = get_int();
		if (low <= n && n <= high) {
			return n;
		}
		std::cout << sorry << ":[" << low << ':' << high << "]\n";
	}
}

void Utils::skip_to_int(std::istream& is) {
	if (is.eof()) {
		throw Invalid{};
	}
	if (is.fail()) {
		is.clear();
		for (char ch; std::cin >> ch;) {
			if (isdigit(ch)) {
				std::cin.unget();
				return;
			}
		}
		is.clear(std::ios_base::failbit);
	}
}