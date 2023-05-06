#pragma once
#include <string>
namespace Util {
	bool next_value(const std::string& target, const int index);
	bool previous_value(const int index);
	int find_duplicates(std::string_view target_string, char c);
	bool duplicate_substrs(std::string_view target_string, std::string_view sub_str);
	bool repeats(const std::string& target_string, char c, unsigned pos);	//returns true if c repeats more than 3 times in succession...
}