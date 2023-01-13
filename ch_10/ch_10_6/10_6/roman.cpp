#include <iostream>
#include <algorithm>
#include "place_value.h"
#include "roman.h"
#include "token.h"
#include "util.h"
Token_stream ts;
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
	int left{};
	for (int i = 0; i < roman_code.size(); ++i) {
		Token t = ts.get(roman_code[i]);
		switch (t.roman_letter) {
		case'I':
		{
			if (Util::find_duplicates(roman_code, roman_code[i]) > repeat_limit) {
				std::cerr << "oops " << roman_code[i] << " can only repeat " << repeat_limit << " times\n";
				throw Invalid{};
			}
			if (Util::next_value(roman_code, i + 1)) {
				if (roman_code[i + 1] == 'V') {
					t = { "IV",4 };
					if (left && left < t.val) {
						std::cerr << "oops cannot subtract from " << t.roman_letters << " ...\n";
						throw Invalid{};
					}
					p.ones += t.val;
					++i;
					break;
				}
				else if (roman_code[i + 1] == 'X') {
					t = { "IX",9 };
					if (left && left < t.val) {
						std::cerr << "oops cannot subtract from " << t.roman_letters << " ...\n";
						throw Invalid{};
					}
					p.ones += t.val;
					++i;
					break;
				}
			}
		}
		++p.ones;
		left += t.val; //test
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
		p.ones += t.val;
		left += t.val;			// test
		break;
		/*	case'X': {
				if (Util::find_duplicates(roman_code, roman_code[i]) > repeat_limit) {
					std::cerr << "oops " << roman_code[i] << " can only repeat " << repeat_limit << " times\n";
					throw Invalid{};
				}
				++p.tens;
				left += 10;
				break;
			}
			default:
				break;
			}*/
		}
	}
	if (p.thousands) {
		value += (Place_value::Multiplier::thousand * p.thousands);
	}
	if (p.hundreds) {
		value += (Place_value::Multiplier::hundred * p.hundreds);
	}
	if (p.tens) {
		value += (Place_value::Multiplier::ten * p.tens);
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