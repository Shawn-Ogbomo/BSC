#include "util.h"
#pragma once

bool Util::next_value(const std::string& target, const int index) {
	if (target[index]) {
		return true;
	}
	return false;
}