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
	std::vector<char>valids = { 'I','V','X','L','C','D','M' };
	for (int i = 0; i < roman_code.size(); ++i) {
		if (islower(symbols[i])) {
			roman_code[i] = toupper(symbols[i]);
		}
		if (auto search = std::find(std::begin(valids), std::end(valids), roman_code[i]) == valids.end()) {
			std::cerr << "Invalid Roman symbol: " << roman_code[i] << "\n";
			throw Invalid{};
		}
	}

	for (int i = 0, count = 1; i < roman_code.size(); ++i) {
		for (int j = i + 1; j < roman_code.size(); ++j) {
			if (roman_code[j] == roman_code[i]) {
				++count;
				if (count == repeat_limit) {
					std::cerr << "Roman numerals can only repeat 3 times consecutively...\n";
					throw Invalid{};
				}
			}
			else if (roman_code[j] != roman_code[i]) {
				count = 0;
			}
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