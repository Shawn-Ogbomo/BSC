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
		auto test = s.find_first_not_of(c, 0) == std::string::npos ? s.size() : s.find_first_not_of(c, 0);

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

void Util::increment(unsigned& index) {
	++index;
}