#include <iostream>
#include <cctype>
#include "roman.h"
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
	for (auto target : symbols) {
		if (islower(target)) {
			target = toupper(target);
		}
		switch (target) {
		case'I':

		case'V':

		case'X':

		case'L':

		case'C':

		case'D':

		case'M':
		default:
			std::cerr << "Invalid Roman symbol...\n";
			throw Invalid{};
			break;
		}
	}
}
int Roman_int::as_int() const {
	return value;
}