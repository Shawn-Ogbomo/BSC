#include <map>
#include <cmath>
#include <iostream>
#include <algorithm>
#include "util.h"
#include "roman.h"
#include "token.h"
#include "place_value.h"

Roman_int::Roman_int() = default;

Roman_int::Roman_int(const std::string& letters)
	: roman_code{ letters } {
	std::for_each(roman_code.begin(), roman_code.end(), [](char& letter) {letter = std::toupper(letter); });

	static const std::map<std::string, int> roman_ints{
	{"I",1},{"IV",4},{"V",5},{"IX",9},{"X",10},
	{ "XL",40 },{"L",50},{ "XC",90 },{"C",100},
	{"CD",400 },{"D",500},{ "CM",900 }, { "M",1000 } };

	const auto rmn_code_sz = roman_code.size();

	for (auto i = 0U; i < rmn_code_sz; ++i) {
		const auto& new_case = Util::lookup(roman_ints, roman_code, i, i + 1);
		auto next_new_case = ((i + 2) < rmn_code_sz) ? roman_ints.find(std::string{ roman_code[i + 2] }) : roman_ints.end();
		auto next = ((i + 1) < rmn_code_sz) ? roman_ints.find(std::string{ roman_code[i + 1] }) : roman_ints.end();
		auto prev = ((i - 1) != -1) ? roman_ints.find(std::string{ roman_code[i - 1] }) : roman_ints.end();

		switch (roman_code[i]) {
		case 'I':
		{
			Util::repeats(roman_code, roman_code[i], i);
			Util::sum(new_case, next_new_case, next, prev, roman_ints, value, roman_code[i]);
			Util::increment(roman_ints, new_case, i);
			break;
		}
		case 'V':
		{
			Util::find_duplicates(roman_code, roman_code[i]);
			Util::sum(new_case, next_new_case, next, prev, roman_ints, value, roman_code[i]);
			break;
		}
		case 'X':
		{
			Util::repeats(roman_code, roman_code[i], i);
			Util::sum(new_case, next_new_case, next, prev, roman_ints, value, roman_code[i]);
			Util::increment(roman_ints, new_case, i);
			break;
		}
		case 'L':
		{
			Util::find_duplicates(roman_code, roman_code[i]);
			Util::sum(new_case, next_new_case, next, prev, roman_ints, value, roman_code[i]);
			break;
		}
		case 'C':
		{
			Util::repeats(roman_code, roman_code[i], i);
			Util::sum(new_case, next_new_case, next, prev, roman_ints, value, roman_code[i]);
			Util::increment(roman_ints, new_case, i);
			break;
		}
		case 'D':
		{
			Util::find_duplicates(roman_code, roman_code[i]);
			Util::sum(new_case, next_new_case, next, prev, roman_ints, value, roman_code[i]);
			break;
		}
		case 'M':
		{
			Util::repeats(roman_code, roman_code[i], i);
			Util::sum(new_case, next_new_case, next, prev, roman_ints, value, roman_code[i]);
			break;
		}
		default:
			throw std::runtime_error{ " Invalid Roman Int...\n" };
		}
	}
}

const int& Roman_int::as_int() const {
	return value;
}

std::string_view Roman_int::as_string() const {
	return roman_code;
}

std::ostream& operator<<(std::ostream& os, const Roman_int& r) {
	return os << r.as_string();
}

std::istream& operator>>(std::istream& is, Roman_int& r) {
	// TODO: insert return statement here
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
			if (!val) {
				return roman_notation;
			}
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
			if (!val) {
				return roman_notation;
			}
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
				else if (p.ones > four.val && p.ones < nine.val) {
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
		throw  std::runtime_error{ "cannot represent " + std::to_string(val) + " as a roman numeral..." };
	}

	throw  std::runtime_error("oops something went wrong...");
}

Roman_int operator+(const Roman_int& value, const Roman_int& right) {
	return Roman_int{ integer_to_roman_code(value.as_int() + right.as_int()) };
}

Roman_int operator-(const Roman_int& value, const Roman_int& right) {
	return Roman_int{ integer_to_roman_code(value.as_int() - right.as_int()) };
}

Roman_int operator*(const Roman_int& value, const Roman_int& right) {
	return Roman_int{ integer_to_roman_code(value.as_int() * right.as_int()) };
}

Roman_int operator/(const Roman_int& value, const Roman_int& right) {
	if (!right.as_int()) {
		throw  std::runtime_error{ "Cannot divide by zero..." };
	}
	return Roman_int{ integer_to_roman_code(value.as_int() / right.as_int()) };
}

Roman_int operator^(const Roman_int& value, const Roman_int& right) {
	return Roman_int{ integer_to_roman_code((std::pow(value.as_int(),right.as_int()))) };
}

Roman_int operator%(const Roman_int& value, const Roman_int& right) {
	if (!right.as_int()) {
		throw  std::runtime_error{ "Cannot mod by " + std::string{std::to_string(right.as_int())} + "..." };
	}
	return Roman_int{ integer_to_roman_code(value.as_int() % right.as_int()) };
}