#include <map>
#include <cmath>
#include <iostream>
#include <algorithm>
#include "util.h"
#include "roman.h"

static const std::map<std::string, int> roman_ints{
{"I",1},{"IV",4},{"V",5},{"IX",9},{"X",10},
{ "XL",40 },{"L",50},{ "XC",90 },{"C",100},
{"CD",400 },{"D",500},{ "CM",900 }, { "M",1000 } };

Roman_int::Roman_int() = default;

Roman_int::Roman_int(const std::string& letters)
	: roman_code{ letters } {
	const auto& rmn_code_sz = roman_code.size();

	for (auto i = 0U; i < rmn_code_sz; ++i) {
		const auto& new_case = Util::build_new_case(roman_ints, roman_code, i, i + 1);

		auto next_new_case = Util::next_or_previous(roman_ints, roman_code, i + 2);
		auto next = Util::next_or_previous(roman_ints, roman_code, i + 1);
		auto prev = Util::next_or_previous(roman_ints, roman_code, i + -1);

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
	char c = (toupper(is.peek()));

	if (auto test = roman_ints.find(std::string{ c }); test == roman_ints.end()) {
		is.clear(std::ios_base::failbit);
		return is;
	}

	std::string s;
	while (is.get(c) && roman_ints.find(std::string{ static_cast<char>((toupper(c))) }) != roman_ints.end()) {
		s += c;
	}

	is.unget();

	Roman_int rmn{ s };
	r = rmn;

	return is;
}

std::string integer_to_roman_code(int val) {
	if (constexpr int max_value = 3999;
		val <= 0 || val > max_value) {
		throw  std::runtime_error{ "cannot represent " + std::to_string(val) + " as a roman numeral..." };
	}

	std::string roman_notation;
	Util::parse_rmn_by_placevalue(roman_notation, roman_ints, 'M', val);
	Util::parse_rmn_by_placevalue(roman_notation, roman_ints, 'C', val, 'D');
	Util::parse_rmn_by_placevalue(roman_notation, roman_ints, 'X', val, 'L');
	Util::parse_rmn_by_placevalue(roman_notation, roman_ints, 'I', val, 'V');
	return roman_notation;
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
	return Roman_int{ integer_to_roman_code(left.as_int() / right.as_int()) };
}

Roman_int operator^(const Roman_int& left, const Roman_int& right) {
	return Roman_int{ integer_to_roman_code((std::pow(left.as_int(),right.as_int()))) };
}

Roman_int operator%(const Roman_int& left, const Roman_int& right) {
	return Roman_int{ integer_to_roman_code(left.as_int() % right.as_int()) };
}