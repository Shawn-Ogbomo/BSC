#include <iostream>
#include <string_view>
#include <algorithm>
#include <string>
#include <vector>
//Write a program that reads strings and for each string outputs the character classification of each character, as defined by the character classification functions presented in §11.6.Note that a character can have several
//classifications(e.g., x is both a letter and an alphanumeric).

using namespace std::string_literals;

void display_character_classification(std::string_view target) {
	for (const auto& c : target) {
		if (isspace(c)) {
			std::cout << c << "\thas a white space classification...\n";
		}

		if (isalpha(c)) {
			std::cout << c << "\thas an alphabet classification...\n";
		}

		if (isdigit(c)) {
			std::cout << c << "\thas a digit classification...\n";
		}

		if (isxdigit(c)) {
			std::cout << c << "\thas a hexadecimal classification...\n";
		}

		if (isupper(c)) {
			std::cout << c << "\thas an uppercase classification...\n";
		}

		if (islower(c)) {
			std::cout << c << "\thas lower case classification...\n";
		}

		if (isalnum(c)) {
			std::cout << c << "\thas letter or digit classification...\n";
		}

		if (iscntrl(c)) {
			std::cout << c << "\thas a control character classification...\n";
		}

		if (ispunct(c)) {
			std::cout << c << "\thas a punctuation character classification...\n";
		}

		if (isgraph(c)) {
			std::cout << c << "\thas a alphabet, digit, or punctuation classification (isgraph())...\n";
		}
	}
}

int main() {
	std::cout << "Please enter a set of strings. Press ctrl+z when finished.\n\n";
	std::vector<std::string> vals;

	for (auto s = ""s; std::getline(std::cin, s); ) {
		vals.push_back(s);
	}

	if (!std::cin) {
		std::for_each(vals.begin(), vals.end(), [](const auto& s) {
			display_character_classification(s); });
	}
}