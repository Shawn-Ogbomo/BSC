#include <iostream>
#include <vector>
#include <sstream>
#include <ios>

using namespace std::string_literals;
//4. Write a program called multi_input.cpp that prompts the user to enter
//several integers in any combination of octal, decimal, or hexadecimal,
//using the 0 and 0x base suffixes; interprets the numbers correctly; and
//converts them to decimal form.Then your program should output the
//values in properly spaced columns like this:
//0x43 hexadecimal converts to 67 decimal
//0123 octal converts to 83 decimal
//65 decimal converts to 65 decimal

void clean_up_mess() {
	std::cerr << "Invalid input. Press ; to continue... ";
	std::cin.clear();

	for (char ch{}; std::cin >> ch;) {
		if (ch == ';') {
			return;
		}
	}
}

int main() {
	std::vector<std::pair<std::string, int>> vals;
	std::cin.unsetf(std::ios::oct);
	std::cin.unsetf(std::ios::hex);

	while (true) {
		std::cout << "Enter a set of values either in decimal,octal,or hex. Press ctrl+z to stop\n\n";

		for (auto s = ""s; std::cin >> s;) {
			std::istringstream is{ s };
			int val{};
			is >> val;
			vals.emplace_back(s, val);
		}

		if (std::cin.eof()) {
			for (const auto& [base, val] : vals) {
				std::cout << base << "converts to\t" << val << "\tdecimal" << "\n";
			}
		}

		else if (!std::cin) {
			clean_up_mess();
		}
	}
}