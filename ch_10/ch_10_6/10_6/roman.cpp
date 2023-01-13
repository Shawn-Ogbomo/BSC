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
			if (Util::repeats(roman_code, roman_code[i])) {
				std::cerr << "oops " << roman_code[i] << " can only repeat " << repeat_limit << " times\n";
				throw Roman_int::Invalid{};
			}
			if (Util::next_value(roman_code, i + 1)) {
				if (roman_code[i + 1] == 'V') {
					t = { "IV",4 };
					if (Util::duplicate_substrs(roman_code, t.roman_letters)) {
						std::cerr << t.roman_letters << " cannot repeat...\n";
						throw Roman_int::Invalid{};
					}
					if (Util::next_value(roman_code, i + 2)) {
						std::cerr << "oops roman numeral after " << t.roman_letters << " is invalid...\n";
						throw Roman_int::Invalid{};
					}
					if (left && left < t.val) {
						std::cerr << "oops cannot subtract from " << t.roman_letters << " ...\n";
						throw Roman_int::Invalid{};
					}
					left += t.val;
					++i;
					break;
				}
				else if (roman_code[i + 1] == 'X') {
					t = { "IX",9 };
					if (Util::duplicate_substrs(roman_code, t.roman_letters)) {
						std::cerr << t.roman_letters << " cannot repeat...\n";
						throw Roman_int::Invalid{};
					}
					if (Util::next_value(roman_code, i + 2)) {
						std::cerr << "oops roman numeral after " << t.roman_letters << " is invalid...\n";
						throw Roman_int::Invalid{};
					}
					if (left && left < t.val) {
						std::cerr << "oops cannot subtract from " << t.roman_letters << " ...\n";
						throw Roman_int::Invalid{};
					}
					left += t.val;
					++i;
					break;
				}
			}
		}
		left += t.val;
		break;
		case'V':
		{
			if (Util::find_duplicates(roman_code, roman_code[i]) > 1) {
				std::cerr << "oops " << roman_code[i] << " cannot repeat...\n";
				throw Roman_int::Invalid{};
			}
			if (Util::next_value(roman_code, i + 1)) {
				if (roman_code[i + 1] != 'I') {
					std::cerr << "Sorry V cannot be subtracted...\n";
					throw Roman_int::Invalid{};
				}
			}
		}
		left += t.val;
		break;
		case 'X':
			if (Util::repeats(roman_code, roman_code[i])) {
				std::cerr << "oops " << roman_code[i] << " can only repeat " << repeat_limit << " times\n";
				throw Roman_int::Invalid{};
			}
			left += t.val;
			break;
		}
	}
	value = left;
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