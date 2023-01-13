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
	if (target_string.size() < 4) {
		throw std::length_error("cant find duplicate sub-strings with a length less than 4...\n");
	}
	if (int pos = target_string.find(sub_str) != std::string::npos) {
		if (int pos2 = target_string.find(sub_str, (pos + 2))) {
			return true;
		}
	}
	return false;
}