#include <iostream>
#include "util.h"
int Utils::get_int() {
	int n = 0;
	while (true) {
		if (std::cin >> n) {
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

void Utils::skip_to_int() {
	if (std::cin.fail()) {
		std::cin.clear();
		for (char ch; std::cin >> ch;) {
			if (isdigit(ch) || ch == '-') {
				std::cin.unget();
				return;
			}
		}
		std::cerr << "no input...\n";
		throw Invalid{};
	}
}