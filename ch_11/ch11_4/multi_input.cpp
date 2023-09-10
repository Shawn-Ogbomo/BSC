#include <iostream>
#include <algorithm>
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

std::istream& operator >> (std::istream& is, std::pair<std::string, int>& p) {
	auto& [base, val] = p;
	is >> base;
	std::istringstream iss{ base };

	iss.unsetf(std::ios::oct);
	iss.unsetf(std::ios::hex);
	iss.unsetf(std::ios::dec);

	iss >> val;

	return is;
}

void display(const std::vector<std::pair<std::string, int>>& vals) {
	std::string_view hex{ "0x" };
	constexpr char oct{ '0' };

	for (const auto& [base, val] : vals) {
		if (std::string_view(base).substr(0, 2) == hex) {
			std::cout << base
				<< " hexadecimal converts to:\t" << val << "\tdecimal" << "\n";
		}

		else if (base[0] == oct) {
			std::cout << base << " octal converts to:\t" << val << "\tdecimal" << "\n";
		}

		else {
			std::cout << base << " decimal converts to:\t" << val << "\tdecimal" << "\n";
		}
	}
}

void convert_to_lower(std::string& target_string) {
	if (!target_string.empty()) {
		std::transform(target_string.cbegin(), target_string.cend(), target_string.begin()
			, [](unsigned char letter) {return std::tolower(letter); });
	}
}

int main() {
	std::vector<std::pair<std::string, int>> vals;

	while (true) {
		std::cout << "Enter a set of values either in decimal,octal,or hex. Press ctrl+z to stop\n\n";

		for (std::pair<std::string, int> p; std::cin >> p;) {
			convert_to_lower(p.first);
			vals.emplace_back(p);
		}

		if (std::cin.eof()) {
			display(vals);
			break;
		}

		if (!std::cin) {
			clean_up_mess();
		}
	}
}