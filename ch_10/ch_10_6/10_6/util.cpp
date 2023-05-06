#include <string_view>
#include <algorithm>
#include <iostream>
#include <cctype>
#include "util.h"

bool Util::next_value(const std::string& target, const int index) {
	if (target[index]) {
		return true;
	}
	return false;
}

bool Util::previous_value(const int index) {
	if (index != std::string::npos) {
		return true;
	}
	return false;
}

int Util::find_duplicates(std::string_view target_string, char c) {
	if (target_string.size()) {
		const int num_items = std::count(target_string.begin(), target_string.end(), c);
		return num_items;
	}
	throw std::length_error("oops, the string is empty...\n");
}

bool Util::duplicate_substrs(std::string_view target_string, std::string_view sub_str) {
	if (sub_str.empty()) {
		throw std::length_error("oops, you passed in an empty string \n");
	}

	if (int pos = target_string.find(sub_str); pos != std::string::npos) {
		if (int pos2 = target_string.find(sub_str, (pos + sub_str.size()))) {
			if (pos2 != std::string::npos) {
				return true;
			}
		}
	}
	return false;
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
	throw std::length_error("oops, the string is empty...\n");
}