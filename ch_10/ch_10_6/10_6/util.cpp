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

bool Util::repeats(const std::string& target_string, char c, unsigned pos) {
	if (!target_string.empty()) {
		constexpr auto repeat_limit = 3;
		const auto max_size = target_string.size();
		auto count = 0;
		for (auto i = pos; i < max_size; ++i) {
			if (c == target_string[i]) {
				++count;
			}
			else if (c != target_string[i]) {
				return false;
			}
			if (count > repeat_limit) {
				return true;
			}
		}
		return false;
	}
	throw std::invalid_argument("oops, the string is empty...\n");
}