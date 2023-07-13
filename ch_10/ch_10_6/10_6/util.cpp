#include <map>
#include <string_view>
#include <algorithm>
#include <iostream>
#include "util.h"

void Util::find_duplicates(std::string_view target_string, char c) {
	if (target_string.size()) {
		if (const int num_items = std::count(target_string.begin(), target_string.end(), c)
			; num_items > 1) {
			throw std::runtime_error{ "Invalid roman int...\n" };
		}
		return;
	}
	throw std::invalid_argument("oops, the string is empty...\n");
}

void Util::repeats(const std::string_view s, char c, unsigned pos) {
	if (!s.empty()) {
		if (const auto num_of_consecutive_characters = s.find_first_not_of(c, pos)
			; num_of_consecutive_characters == std::string::npos) {
			if (s.size() > 3) {
				throw std::runtime_error{ "Invalid roman int...\n" };
			}
		}

		else if (num_of_consecutive_characters - pos > 3) {
			throw std::runtime_error{ "Invalid roman int...\n" };
		}
		return;
	}

	throw std::invalid_argument("oops, the string is empty...\n");
}

void Util::increment(const std::map<std::string, int>& map
	, const std::map<std::string, int>::const_iterator it, unsigned& index) {
	if (it != map.end())
		++index;
}

std::map<std::string, int>::const_iterator Util::lookup(const std::map <std::string, int>& m
	, std::string_view rmn_code, int current_index, int new_index) {
	if (new_index && (new_index < rmn_code.size())) {
		return m.find(rmn_code[current_index] + std::string{ rmn_code[new_index] });
	}
	return m.end();
}

void::Util::sum(const std::map<std::string, int>::const_iterator it1_new_case
	, const std::map<std::string, int>::const_iterator it2_next_new_case
	, const std::map<std::string, int>::const_iterator it3_next
	, const std::map<std::string, int>::const_iterator it4_prev
	, const std::map<std::string, int>& map, int& val, char c) {
	if (it1_new_case != map.end()) {
		if ((it2_next_new_case != map.end() && it2_next_new_case->second >= map.find(std::string{ c })->second)
			|| ((it4_prev != map.end()) && (it4_prev->second < it3_next->second))) {
			throw std::runtime_error{ "Invalid roman int...\n" };
		}
		val += map.find(it1_new_case->first)->second;
	}

	else if (it3_next != map.end() && it3_next->second > map.find(std::string{ c })->second
		|| it4_prev != map.end() && it4_prev->second < map.find(std::string{ c })->second) {
		throw std::runtime_error{ "Invalid roman int...\n" };
	}

	else {
		val += map.find(std::string{ c })->second;
	}
}