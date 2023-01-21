#include <iostream>
#include <vector>
#include "roman.h"
#include "token.h"
#include "place_value.h"
#include "util.h"
Roman_int::Roman_int()
	:roman_code{ "nulla" },
	roman_character{},
	value{}{
}
Roman_int::Roman_int(const char letter)
	: roman_character{ letter },
	value{},
	roman_code{} {
	if (islower(roman_character)) {
		roman_character = toupper(roman_character);
	}
	Token_gen::Token t = Token_gen::get(roman_character);
	value = t.val;
}
Roman_int::Roman_int(const std::string& letters)
	: roman_code{ letters },
	roman_character{},
	value{}{
	if (!roman_code.size() || letters == "nulla") {
		roman_code = "nulla";
		value = 0;
		return;
	}
	for (int i = 0; i < roman_code.size(); ++i) {
		if (islower(roman_code[i])) {
			roman_code[i] = toupper(roman_code[i]);
		}
	}
	int left{};
	for (int i = 0; i < roman_code.size(); ++i) {
		Token_gen::Token t = Token_gen::get(roman_code[i]);
		switch (t.roman_letter) {
		case'I':
		{
			if (Util::repeats(roman_code, roman_code[i])) {
				throw Roman_int::Parse_error{ "oops " + std::string{roman_code[i]} + " can only repeat " + std::to_string(repeat_limit) + " times" };
			}
		}
		if (Util::next_value(roman_code, i + 1)) {
			if (roman_code[i + 1] == 'V') {
				t = { "IV",4 };
				if (Util::duplicate_substrs(roman_code, t.roman_letters)) {
					throw Roman_int::Parse_error{ t.roman_letters + " cannot repeat..." };
				}
				if (Util::next_value(roman_code, i + 2)) {
					throw Roman_int::Parse_error{ "oops roman numeral after " + t.roman_letters + " is invalid..." };
				}
				if (Util::previous_value(i - 1)) {
					Token_gen::Token t2 = Token_gen::get(roman_code[i - 1]);
					if (t2.val < t.val) {
						throw Roman_int::Parse_error{ "oops cannot subtract from " + t.roman_letters + "..." };
					}
				}
				left += t.val;
				++i;
				break;
			}
			else if (roman_code[i + 1] == 'X') {
				t = { "IX",9 };
				if (Util::duplicate_substrs(roman_code, t.roman_letters)) {
					throw Roman_int::Parse_error{ t.roman_letters + " cannot repeat..." };
				}
				if (Util::next_value(roman_code, i + 2)) {
					throw Roman_int::Parse_error{ "oops roman numeral after " + t.roman_letters + " is invalid..." };
				}
				if (Util::previous_value(i - 1)) {
					Token_gen::Token t2 = Token_gen::get(roman_code[i - 1]);
					if (t2.val < t.val) {
						throw Roman_int::Parse_error{ "oops cannot subtract from " + t.roman_letters + " ..." };
					}
				}
				left += t.val;
				++i;
				break;
			}
		}
		left += t.val;
		break;
		case'V':
		{
			if (Util::find_duplicates(roman_code, roman_code[i]) > 1) {
				throw Roman_int::Parse_error{ "oops " + std::string{roman_code[i]} + " cannot repeat..." };
			}
			if (Util::next_value(roman_code, i + 1)) {
				Token_gen::Token t2 = Token_gen::get(roman_code[i + 1]);
				if (t2.roman_letter != 'I') {
					throw Roman_int::Parse_error{ "Sorry " + std::string{t.roman_letter} + " cannot be subtracted..." };
				}
			}
		}
		left += t.val;
		break;
		case 'X':
		{
			if (Util::repeats(roman_code, roman_code[i])) {
				throw Roman_int::Parse_error{ "oops " + std::string{roman_code[i]} + " can only repeat " + std::to_string(repeat_limit) + " times\n" };
			}
			if (Util::next_value(roman_code, i + 1)) {
				if (roman_code[i + 1] == 'L') {
					t = { "XL",40 };
					if (Util::duplicate_substrs(roman_code, t.roman_letters)) {
						throw Roman_int::Parse_error{ t.roman_letters + " cannot repeat...\n" };
					}
					if (Util::next_value(roman_code, i + 2)) {
						Token_gen::Token t2 = Token_gen::get(roman_code[i + 2]);
						if (t2.roman_letter != 'I' && t2.roman_letter != 'V') {
							throw Roman_int::Parse_error{ std::string{t2.roman_letter} + " cannot proceed " + t.roman_letters + "..." };
						}
					}
					if (Util::previous_value(i - 1)) {
						Token_gen::Token t2 = Token_gen::get(roman_code[i - 1]);
						if (t2.val < t.val) {
							throw Roman_int::Parse_error{ "oops cannot subtract from " + t.roman_letters + " ..." };
						}
					}
					left += t.val;
					++i;
					break;
				}
				else if (roman_code[i + 1] == 'C') {
					t = { "XC",90 };
					if (Util::duplicate_substrs(roman_code, t.roman_letters)) {
						throw Roman_int::Parse_error{ t.roman_letters + " cannot repeat..." };
					}
					if (Util::next_value(roman_code, i + 2)) {
						Token_gen::Token t2 = Token_gen::get(roman_code[i + 2]);
						if (t2.roman_letter != 'I' && t2.roman_letter != 'V') {
							throw Roman_int::Parse_error{ std::string{t2.roman_letter} + " cannot proceed " + t.roman_letters + "..." };
						}
					}
					if (Util::previous_value(i - 1)) {
						Token_gen::Token t2 = Token_gen::get(roman_code[i - 1]);
						if (t2.val < t.val) {
							throw Roman_int::Parse_error{ "oops cannot subtract from " + t.roman_letters + "..." };
						}
					}
					left += t.val;
					++i;
					break;
				}
			}
			left += t.val;
			break;
		}
		case 'L':
		{
			if (Util::find_duplicates(roman_code, roman_code[i]) > 1) {
				throw Roman_int::Parse_error{ "oops " + std::string{roman_code[i]} + " cannot repeat..." };
			}
			if (Util::previous_value(i - 1)) {
				Token_gen::Token t2 = Token_gen::get(roman_code[i - 1]);
				if (t2.val < t.val) {
					throw Roman_int::Parse_error{ "oops cannot subtract from " + std::string{t.roman_letter} + "..." };
				}
			}
			if (Util::next_value(roman_code, i + 1)) {
				Token_gen::Token t2 = Token_gen::get(roman_code[i + 1]);
				if (t2.val > t.val) {
					throw Roman_int::Parse_error{ "Sorry " + std::to_string(t.roman_letter) + " cannot be subtracted...\n" };
				}
			}
			left += t.val;
			break;
		}
		case 'C':
		{
			if (Util::repeats(roman_code, roman_code[i])) {
				throw Roman_int::Parse_error{ "Invalid syntax..." };
			}
			if (Util::previous_value(i - 1)) {
				Token_gen::Token t2 = Token_gen::get(roman_code[i - 1]);
				if (t2.val < t.val) {
					throw Roman_int::Parse_error{ "oops cannot subtract " + std::string{t2.roman_letter} + " from " + t.roman_letter + "..." };
				}
			}
			if (Util::next_value(roman_code, i + 1)) {
				if (roman_code[i + 1] == 'D') {
					t = { "CD",400 };
					if (Util::duplicate_substrs(roman_code, t.roman_letters)) {
						throw Roman_int::Parse_error{ t.roman_letters + " cannot repeat...\n" };
					}
					if (Util::next_value(roman_code, i + 2)) {
						Token_gen::Token t2 = Token_gen::get(roman_code[i + 2]);
						if (t2.roman_letter != 'I' && t2.roman_letter != 'V' && t2.roman_letter != 'X' && t2.roman_letter != 'L') {
							throw Roman_int::Parse_error{ std::string{t2.roman_letter} + " cannot proceed " + t.roman_letters + "..." };
						}
					}
					if (Util::previous_value(i - 1)) {
						Token_gen::Token t2 = Token_gen::get(roman_code[i - 1]);
						if (t2.val < t.val) {
							throw Roman_int::Parse_error{ "oops cannot subtract from " + t.roman_letters + "..." };
						}
					}
					left += t.val;
					++i;
					break;
				}
				if (roman_code[i + 1] == 'M') {
					t = { "CM",900 };
					if (Util::duplicate_substrs(roman_code, t.roman_letters)) {
						throw Roman_int::Parse_error{ t.roman_letters + " cannot repeat..." };
					}
					if (Util::next_value(roman_code, i + 2)) {
						Token_gen::Token t2 = Token_gen::get(roman_code[i + 2]);
						if (t2.roman_letter != 'I' && t2.roman_letter != 'V' && t2.roman_letter != 'X' && t2.roman_letter != 'L') {
							throw Roman_int::Parse_error{ std::string{ t2.roman_letter} + " cannot proceed " + t.roman_letters + "..." };
						}
					}
					if (Util::previous_value(i - 1)) {
						Token_gen::Token t2 = Token_gen::get(roman_code[i - 1]);
						if (t2.val < t.val) {
							throw Roman_int::Parse_error{ "oops cannot subtract from " + t.roman_letters + "..." };
						}
					}
					left += t.val;
					++i;
					break;
				}
			}
			left += t.val;
			break;
		}
		case 'D':
		{
			if (Util::find_duplicates(roman_code, roman_code[i]) > 1) {
				throw Roman_int::Parse_error{ "oops " + std::string{roman_code[i]} + " cannot repeat..." };
			}
			if (Util::previous_value(i - 1)) {
				Token_gen::Token t2 = Token_gen::get(roman_code[i - 1]);
				if (t2.val < t.val) {
					throw Roman_int::Parse_error{ "oops cannot subtract " + std::string{t2.roman_letter} + " from " + t.roman_letter + "..." };
				}
			}
			if (Util::next_value(roman_code, i + 1)) {
				Token_gen::Token t2 = Token_gen::get(roman_code[i + 1]);
				if (t2.val > t.val) {
					throw Roman_int::Parse_error{ "Sorry " + std::string{t.roman_letter} + " cannot be subtracted..." };
				}
			}
			left += t.val;
			break;
		}
		case 'M':
		{
			if (Util::repeats(roman_code, roman_code[i])) {
				throw Roman_int::Parse_error{ "Invalid syntax..." };
			}
			if (Util::previous_value(i - 1)) {
				Token_gen::Token t2 = Token_gen::get(roman_code[i - 1]);
				if (t2.val < t.val) {
					throw Roman_int::Parse_error{ "oops cannot subtract " + std::string{t2.roman_letter} + " from " + t.roman_letter + "..." };
				}
			}
			left += t.val;
			break;
		}
		}
		value = left;
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
std::istream& operator>>(std::istream& is, Roman_int& r) {
	char c{};
	std::string s;
	while (std::cin.get(c) && (isalpha(c) || ispunct(c))) s += c;
	std::cin.unget();
	if (!is) {
		return is;
	}
	r = Roman_int(s);
	return is;
}
std::string integer_to_roman_code(int val) {
	constexpr int max_value = 3999;
	if (val > 0 && val <= max_value) {
		Place_value p;
		std::string roman_notation;
		int result{};
		constexpr int repeat_limit = 3;
		if (result = val / Place_value::Multiplier::thousand) {
			p.thousands = result;
			for (int i{}; i < p.thousands; ++i) {
				roman_notation += 'M';
			}
			val -= (p.thousands * Place_value::Multiplier::thousand);
		}
		if (result = val / Place_value::Multiplier::hundred) {
			p.hundreds = result;
			if (p.hundreds > repeat_limit) {
				Token_gen::Token four_hundred = { "CD",400 };
				Token_gen::Token five_hundred = { 'D',500 };
				Token_gen::Token nine_hundred = { "CM",900 };
				if (p.hundreds * Place_value::Multiplier::hundred == four_hundred.val) {
					roman_notation += four_hundred.roman_letters;
				}
				else if ((p.hundreds * Place_value::Multiplier::hundred) > four_hundred.val && (p.hundreds * Place_value::Multiplier::hundred) < nine_hundred.val) {
					roman_notation += five_hundred.roman_letter;
					for (int i{}, place_value_hundreds_cpy = p.hundreds; i < ((place_value_hundreds_cpy * Place_value::Multiplier::hundred) - five_hundred.val); ++i) {
						roman_notation += 'C';
						--place_value_hundreds_cpy;
					}
				}
				else if (p.hundreds * Place_value::Multiplier::hundred == nine_hundred.val) {
					roman_notation += nine_hundred.roman_letters;
				}
			}
			else {
				for (int i{}; i < p.hundreds; ++i) {
					roman_notation += 'C';
				}
			}
			val -= (p.hundreds * Place_value::Multiplier::hundred);
		}
		if (result = val / Place_value::Multiplier::ten) {
			p.tens = result;
			if (p.tens > repeat_limit) {
				Token_gen::Token fourty = { "XL",40 };
				Token_gen::Token fifty = { 'L',50 };
				Token_gen::Token ninety = { "XC",90 };
				if ((p.tens * Place_value::Multiplier::ten) == fourty.val) {
					roman_notation += fourty.roman_letters;
				}
				else if ((p.tens * Place_value::Multiplier::ten) > fourty.val && (p.tens * Place_value::Multiplier::ten) < ninety.val) {
					roman_notation += fifty.roman_letter;
					for (int i{}, place_value_tens_cpy = p.tens; i < ((place_value_tens_cpy * Place_value::Multiplier::ten) - fifty.val); ++i) {
						roman_notation += 'X';
						--place_value_tens_cpy;
					}
				}
				else if (p.tens * Place_value::Multiplier::ten == ninety.val) {
					roman_notation += ninety.roman_letters;
				}
			}
			else {
				for (int i{}; i < p.tens; ++i) {
					roman_notation += 'X';
				}
			}
			val -= (p.tens * Place_value::Multiplier::ten);
			if (!val) {
				return roman_notation;
			}
		}
		if (val) {
			p.ones = val;
			if (p.ones > repeat_limit) {
				Token_gen::Token four = { "IV",4 };
				Token_gen::Token five = { 'V',5 };
				Token_gen::Token nine = { "IX",9 };
				if (p.ones == four.val) {
					roman_notation += four.roman_letters;
				}
				else if ((p.ones > four.val && p.ones < nine.val)) {
					roman_notation += five.roman_letter;
					for (int i{}, place_value_ones_cpy = p.ones; i < (place_value_ones_cpy - five.val); ++i) {
						roman_notation += 'I';
					}
				}
				else if (p.ones == nine.val) {
					roman_notation += nine.roman_letters;
				}
			}
			else {
				for (int i{}; i < p.ones; ++i) {
					roman_notation += 'I';
				}
			}
			return roman_notation;
		}
	}
	if (!val) {
		return std::string{ "nulla" };
	}
	if (val > max_value || val < 0) {
		throw Roman_int::Invalid{ "cannot represent " + std::to_string(val) + " as a roman numeral..." };
	}
	throw Roman_int::Invalid("oops, something went wrong...");
}
Roman_int operator+(const Roman_int& left, const Roman_int& right) {
	return Roman_int{ integer_to_roman_code(left.as_int() + right.as_int()) };
}

Roman_int operator-(const Roman_int& left, const Roman_int& right) {
	return Roman_int{ integer_to_roman_code(left.as_int() - right.as_int()) };
}
Roman_int operator*(const Roman_int& left, const Roman_int& right) {
	return Roman_int{ integer_to_roman_code(left.as_int() * right.as_int()) };
}
Roman_int operator/(const Roman_int& left, const Roman_int& right) {
	if (!right.as_int()) {
		throw Roman_int::Invalid{ "Cannot divide by zero..." };
	}
	return Roman_int{ integer_to_roman_code(left.as_int() / right.as_int()) };
}