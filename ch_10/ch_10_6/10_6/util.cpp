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