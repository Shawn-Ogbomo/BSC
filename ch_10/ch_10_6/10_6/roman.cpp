#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include "place_value.h"
#include "roman.h"
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
			if (Util::find_duplicates(roman_code, roman_code[i]) > repeat_limit) {
				std::cerr << "oops " << roman_code[i] << " can only repeat " << repeat_limit << " times\n";
				throw Invalid{};
			}
			if (Util::next_value(roman_code, i + 1)) {
				if (roman_code[i + 1] == 'V') {
					p.ones += 4;
					i += 2;
					break;
				}
				else if (roman_code[i + 1] == 'X') {
					if (p.ones < 10) {
						std::cerr << "oops cannot subtract " << p.ones << " from " << roman_code[i] << "\n";
						throw Invalid{};
					}
					p.ones += 9;
					i += 2;
					break;
				}
			}
		}
		++p.ones;
		break;
		case'V':
		{
			if (Util::find_duplicates(roman_code, roman_code[i]) > 1) {
				std::cerr << "oops " << roman_code[i] << " cannot repeat...\n";
				throw Invalid{};
			}
			if (Util::next_value(roman_code, i + 1)) {
				if (roman_code[i + 1] != 'I') {
					std::cerr << "Sorry V cannot be subtracted...\n";
					throw Invalid{};
				}
			}
		}
		p.ones += 5;
		break;
		case'X': {
			if (Util::find_duplicates(roman_code, roman_code[i]) > repeat_limit) {
				std::cerr << "oops " << roman_code[i] << " can only repeat " << repeat_limit << " times\n";
				throw Invalid{};
			}
			++p.tens;
			break;
		}
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