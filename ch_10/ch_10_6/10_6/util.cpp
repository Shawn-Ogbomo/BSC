#include <map>
#include <iostream>
#include <algorithm>
#include <string_view>
#include "exceptions.h"
#include "util.h"

void Util::find_duplicates(std::string_view target_string, char c) {
	if (const int num_items = std::count(target_string.begin(), target_string.end(), c)
		; num_items > 1) {
		throw std::runtime_error{ "Invalid roman int...\n" };
	}
}

void Util::repeats(const std::string_view s, char c, unsigned pos) {
	if (const auto num_of_consecutive_characters = s.find_first_not_of(c, pos)
		; (num_of_consecutive_characters == std::string::npos)
		&& (s.size() - pos > 3)
		|| (num_of_consecutive_characters != std::string::npos)
		&& (num_of_consecutive_characters - pos > 3)) {
		throw std::runtime_error{ "Invalid roman int...\n" };
	}
}

void Util::increment(const std::map<std::string, int>& map
	, const std::map<std::string, int>::const_iterator it, unsigned& index) {
	if (it == map.end()) {
		return;
	}

	++index;
}

std::map<std::string, int>::const_iterator Util::lookup(const std::map <std::string, int>& m
	, std::string_view rmn_code, int current_index, int new_index) {
	if (new_index == rmn_code.size()) {
		return m.end();
	}

	return m.find(rmn_code[current_index] + std::string{ rmn_code[new_index] });
}

void::Util::sum(const std::map<std::string, int>::const_iterator it1_new_case
	, const std::map<std::string, int>::const_iterator it2_next_new_case
	, const std::map<std::string, int>::const_iterator it3_next
	, const std::map<std::string, int>::const_iterator it4_prev
	, const std::map<std::string, int>& map, int& val, char c) {
	std::string c_as_string{ c };

	if (it1_new_case != map.end()) {
		if ((it2_next_new_case != map.end() && it2_next_new_case->second >= map.find(c_as_string)->second)
			|| ((it4_prev != map.end()) && (it4_prev->second < it3_next->second))) {
			throw std::runtime_error{ "Invalid roman int...\n" };
		}
		val += map.find(it1_new_case->first)->second;
	}

	else if (it3_next != map.end() && it3_next->second > map.find(c_as_string)->second
		|| it4_prev != map.end() && it4_prev->second < map.find(c_as_string)->second) {
		throw std::runtime_error{ "Invalid roman int...\n" };
	}

	else {
		val += map.find(c_as_string)->second;
	}
}

void Util::parse_rmn_by_placevalue(std::string& result, const std::map<std::string
	, int>& map, char rmn_letter, int& val, char next_rmn_letter) {
	const auto place_value = map.find(std::string{ rmn_letter })->second;
	const auto rmn_letter_qty = val / place_value;
	const auto repeat_limit = 3;

	if (rmn_letter_qty > 0 && rmn_letter_qty <= repeat_limit) {
		result.append(val / place_value, rmn_letter);
		val -= ((val / place_value) * place_value);
	}

	else if (rmn_letter_qty > repeat_limit) {
		const auto total = rmn_letter_qty * place_value;
		for (const auto& [key, value] : map) {
			if (total == value) {
				result += key;
				val -= value;
				return;
			}
		}

		result.append(1, next_rmn_letter);
		val -= map.find(std::string{ next_rmn_letter })->second;
		result.append(val / place_value, rmn_letter);
		val -= val;
	}
}

void Util::format_string(std::string& target_string) {
	if (!target_string.empty()) {
		target_string[0] = toupper(target_string[0]);
		std::transform(target_string.cbegin() + 1, target_string.cend(), target_string.begin() + 1
			, [](unsigned char letter) {return std::tolower(letter); });
	}
}

void Util::skip_input(std::istream& is, char terminator) {
	is.clear();

	const std::string pattern = "+-*/=;()$%^#~"
		"IVXLCDM"
		"cex";

	for (char ch{}; is.get(ch);) {
		if (ch == terminator || ch == '\n' || pattern.find(ch) != std::string::npos) {
			is.unget();
			return;
		}
	}
}

void Util::check_stream(std::istream& is, const std::string& message, const std::string& message2) {
	if (is.eof() || std::cin.eof()) {
		throw Terminate{ message + message2 };
	}

	if (is.fail()) {
		is.clear();
		throw std::runtime_error{ message };
	}
}