#include <iostream>
#include "util.h"
#pragma once
bool Util::next_value(const std::string& target, const int index) {
	if (target[index]) {
		return true;
	}
	return false;
}

int Util::find_duplicates(const std::string& target_string, char c) {
	if (target_string.size()) {
		const int num_items = std::count(target_string.begin(), target_string.end(), c);
		return num_items;
	}
	throw std::length_error("oops, the string is empty...\n");
}

bool Util::duplicate_substrs(const std::string& target_string, const std::string& sub_str) {
	if (sub_str.size() < 2) {
		throw std::length_error("oops, you either passed in an empty string or a character.\nWe need a string that has a size of 2...\n");
	}
	if (target_string.find(sub_str) != std::string::npos) {
		int pos = target_string.find(sub_str);
		if (int pos2 = target_string.find(sub_str, (pos + sub_str.size()))) {
			if (pos2 == std::string::npos) {
				return false;
			}
			return true;
		}
	}
	return false;
}

bool Util::repeats(std::string& target_string, char c) {
	constexpr int repeat_limit = 3;
	if (target_string.size()) {
		int count = 1;
		for (int i = 0; i < target_string.size(); ++i) {
			for (int j = i + 1; j < target_string.size(); ++j) {
				if (target_string[j] == target_string[i]) {
					++count;
					if (count > repeat_limit) {
						return true;
					}
				}
				else if (target_string[j] != target_string[i]) {
					count = 0;
				}
			}
		}
		return false;
	}
	throw std::length_error("oops, the string is empty...\n");
}