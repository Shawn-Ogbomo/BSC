#include <iostream>
#include <vector>
#include "place_value.h"
#include "roman.h"
#include "token.h"
#include "util.h"
Roman_int::Roman_int()
	:roman_code{ "nulla" },
	value{}{
}
Roman_int::Roman_int(const std::string& symbols)
	: roman_code{ symbols },
	value{}{
	Place_value p;
	for (int i = 0; i < roman_code.size(); ++i) {
		if (islower(roman_code[i])) {
			roman_code[i] = toupper(roman_code[i]);
		}
	}

	for (int i = 0; i < roman_code.size(); ++i) {
		switch (roman_code[i]) {
		case'I':
		{
			if (Util::next_value(roman_code, i + 1)) {
				if (roman_code[i + 1] == 'V') {
					p.ones += 4;
					i += 2;
					break;
				}
				else if (roman_code[i + 1] == 'X') {
					p.ones += 9;
					i += 2;
					break;
				}
				++p.ones;
				break;
			}
		}
		case'V':
			break;
		case'X': {
			++p.tens;
			break;
		}
		case'L':
			break;
		case'C':
			break;
		case'D':
			break;
		case'M':
			break;
		default:
			std::cerr << "Invalid Roman symbol...\n";
			throw Invalid{};
		}
	}
	if (p.thousands) {
		value += (1000 * p.thousands);
	}
	if (p.hundreds) {
		value += (100 * p.hundreds);
	}
	if (p.tens) {
		value += (10 * p.tens);
	}
	if (p.ones) {
		value += (p.ones);
	}
}
int Roman_int::as_int() const {
	return value;
}
std::string Roman_int::as_string() const {
	return roman_code;
}
std::ostream& operator<<(std::ostream& os, const Roman_int& r) {
	return os << r.as_string();
}