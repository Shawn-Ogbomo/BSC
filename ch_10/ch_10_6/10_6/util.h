#pragma once
#include <string_view>
#include <functional>
#include <string>
#include <map>

namespace Util {
	int find_duplicates(std::string_view target_string, char c);

	bool repeats(const std::string_view s, char c, unsigned pos);	//returns true if c repeats more than 3 times in succession...

	void increment(const std::map<std::string, int>& map, const std::map<std::string, int, std::less<>>::const_iterator it, unsigned& index);

	std::map<std::string, int>::const_iterator lookup(const std::map <std::string, int>& m, std::string_view rmn_code, int current_index, int new_index);

	void sum(const std::map<std::string, int>::const_iterator it1
		, const std::map<std::string, int>::const_iterator it2
		, const std::map<std::string, int>::const_iterator it3
		, const std::map<std::string, int>::const_iterator it4
		, const std::map<std::string, int>& map, int& val, char c);
}