#include <iostream>
#include <algorithm>
#include <vector>
#include <cctype>
#include "roman.h"
#include "util.h"
Roman_int::Roman_int()
	:roman_code{ "nulla" },
	value{}{
}
Roman_int::Roman_int(const std::string& symbols)
	: roman_code{ symbols },
	value{}{
	if (symbols.size() > max_sz) {
		std::cerr << "Too many symbols...\n";
		throw Invalid{};
	}
	std::vector<std::pair<char, int>>toks;
	for (int i = 0; i < roman_code.size(); ++i) {
		if (islower(roman_code[i])) {
			roman_code[i] = toupper(symbols[i]);
		}
		switch (roman_code[i]) {
		case 'I':
			toks.push_back({ roman_code[i], 1 });
			break;
		case 'V':
			toks.push_back({ roman_code[i], 5 });
			break;
		case 'X':
			toks.push_back({ roman_code[i], 10 });
			break;
		case 'L':
			toks.push_back({ roman_code[i], 50 });
			break;
		case 'C':
			toks.push_back({ roman_code[i], 100 });
			break;
		case 'D':
			toks.push_back({ roman_code[i], 500 });
			break;
		case 'M':
			toks.push_back({ roman_code[i], 1000 });
			break;
		default:
			std::cerr << "Invalid roman symbol " << roman_code[i] << " \n";
			throw Invalid{};
		}
	}
}
int Roman_int::as_int() const {
	return value;
}

std::string Roman_int::as_symbols() const {
	return roman_code;
}
std::ostream& operator<<(std::ostream& os, const Roman_int& r) {
	return os << r.as_symbols();
}