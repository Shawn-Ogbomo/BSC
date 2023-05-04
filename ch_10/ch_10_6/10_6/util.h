#pragma once
#include <string>
namespace Util {
	bool next_value(const std::string& target, const int index);
	bool previous_value(const int index);
	int find_duplicates(const std::string& target_string, char c);
	bool duplicate_substrs(const std::string& target_string, const std::string& sub_str);
	bool repeats(const std::string& target_string, char c, unsigned pos);	//returns true if c repeats more than 3 times in succession...
	void clear_white_space(std::istream& ist = std::cin);
}