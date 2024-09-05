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
		case 'X':
		case 'C':
		case'M':
		{
			Util::repeats(roman_code, roman_code[i], i);
			Util::sum(new_case, next_new_case, next, prev, roman_ints, value, roman_code[i]);
			Util::increment(roman_ints, new_case, i);
			break;
		}
		case 'V':
		case 'L':
		case'D':
		{
			Util::find_duplicates(roman_code, roman_code[i]);
			Util::sum(new_case, next_new_case, next, prev, roman_ints, value, roman_code[i]);
			break;
		}

		default:
			throw std::invalid_argument{ " Invalid Roman Int...\n" };
		}
	}
}

auto Roman_int::as_int() const -> const int&
{
	return value;
}

auto Roman_int::as_string() const -> std::string_view
{
	return roman_code;
}

auto operator<<(std::ostream& os, const Roman_int& r) -> std::ostream&
{
	return os << r.as_string();
}

auto operator>>(std::istream& is, Roman_int& r) -> std::istream&
{
	if (std::istream::sentry s{ is })
	{
		auto c = static_cast<char>(toupper(is.peek()));

		if (auto test = roman_ints.find(std::string{ c }); test == roman_ints.end()) {
			is.clear(std::ios_base::failbit);
			return is;
		}

		std::string internal_s;
		while (is.get(c) && roman_ints.find(std::string{ static_cast<char>((toupper(c))) }) != roman_ints.end()) {
			internal_s += c;
		}

		is.unget();

		Roman_int rmn{ internal_s };
		r = rmn;
	}

	return is;
}

auto integer_to_roman_code(int val) -> std::string
{
	if (const auto max_value = 3999; val <= 0 || val > max_value)
	{
		throw  std::invalid_argument{ "cannot represent " + std::to_string(val) + " as a roman numeral..." };
	}

	std::string roman_notation;

	Util::parse_rmn_by_placevalue(roman_notation, roman_ints, 'M', val);
	Util::parse_rmn_by_placevalue(roman_notation, roman_ints, 'C', val, 'D');
	Util::parse_rmn_by_placevalue(roman_notation, roman_ints, 'X', val, 'L');
	Util::parse_rmn_by_placevalue(roman_notation, roman_ints, 'I', val, 'V');

	return roman_notation;
}

auto operator+(const Roman_int& left, const Roman_int& right) -> Roman_int
{
	return Roman_int{ integer_to_roman_code(left.value + right.value) };
}

auto operator-(const Roman_int& left, const Roman_int& right) -> Roman_int
{
	return Roman_int{ integer_to_roman_code(left.value - right.value) };
}

auto operator*(const Roman_int& left, const Roman_int& right) -> Roman_int
{
	return Roman_int{ integer_to_roman_code(left.value * right.value) };
}

auto operator/(const Roman_int& left, const Roman_int& right) -> Roman_int
{
	return Roman_int{ integer_to_roman_code(left.value / right.value) };
}

auto operator^(const Roman_int& left, const Roman_int& right) -> Roman_int
{
	return Roman_int{ integer_to_roman_code(static_cast<int>(std::pow(left.value,right.value))) };
}

auto operator%(const Roman_int& left, const Roman_int& right) -> Roman_int
{
	return Roman_int{ integer_to_roman_code(left.value % right.value) };
}