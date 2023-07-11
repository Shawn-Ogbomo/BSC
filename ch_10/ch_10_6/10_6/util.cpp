#include <map>
#include <string_view>
#include <algorithm>
#include <iostream>
#include <cctype>
#include "util.h"

int Util::find_duplicates(std::string_view target_string, char c) {
	if (target_string.size()) {
		const int num_items = std::count(target_string.begin(), target_string.end(), c);
		return num_items;
	}
	throw std::invalid_argument("oops, the string is empty...\n");
}

bool Util::repeats(const std::string_view s, char c, unsigned pos) {
	if (!s.empty()) {
		auto test = s.find_first_not_of(c, pos) == std::string::npos ? s.size() : s.find_first_not_of(c, pos);

		if (auto internal_num_items = std::count_if(s.begin() + pos, s.begin()
			+ test, [c](auto ch) {
				return ch = c;
			}); internal_num_items > 3) {
			return true;
		}
		return false;
	}

	throw std::invalid_argument("oops, the string is empty...\n");
}

void Util::increment(const std::map<std::string, int>& map, const std::map<std::string, int>::const_iterator it, unsigned& index) {
	if (it != map.end())
		++index;
}

std::map<std::string, int>::const_iterator Util::lookup(const std::map <std::string, int>& m, std::string_view rmn_code, int current_index, int new_index) {
	if (new_index && (new_index < rmn_code.size())) {
		return m.find(rmn_code[current_index] + std::string{ rmn_code[new_index] });
	}
	return m.end();
}

void::Util::sum(const std::map<std::string, int>::const_iterator it1
	, const std::map<std::string, int>::const_iterator it2
	, const std::map <std::string, int> ::const_iterator it3
	, const std::map<std::string, int>::const_iterator it4
	, const std::map<std::string, int>& map, int& val, char c) {
	//FUNCTION TO REDUCE COGNITIVE COMPLEXITY OF 1 ARGUMENT CONSTRUCTOR ROMAN INT
	// ACCEPT ALL ITERATORS
	//NEW_CASE
	//NEXT_NEW_CASE
	//NEXT
	//PREV

	//ACCEPT THE MAP
	//ACCEPT THE VALUE
	// CURRENT CASE LETTER

	//NEW CASE
	if ((it1 != map.end()) && (it2 != map.end()
		|| (it4 != map.end()) && (it4->first == std::string{ c }
			|| it3->first == map.find(it3->first)->first))) {
		throw std::runtime_error{ "Invalid roman int...\n" };
	}

	else if (it3 != map.end() && it3->first != "I") {
		throw std::runtime_error{ "Invalid roman int...\n" };
	}

	else if (it1 != map.end()) {
		val += map.find(it1->first)->second;
	}

	else {
		//NOT NEW CASE
		val += map.find(std::string{ c })->second;
	}
}