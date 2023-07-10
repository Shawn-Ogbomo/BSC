#pragma once
#include <string_view>
#include <functional>
#include <string>
#include <map>

namespace Util {
	int find_duplicates(std::string_view target_string, char c);
	bool repeats(const std::string& target_string, char c, unsigned pos);	//returns true if c repeats more than 3 times in succession...
	inline auto lookup(const std::map <std::string, int, std::less<>>& m, std::string_view rmn_code, int current_index, int new_index) {
		if (new_index && (new_index < rmn_code.size())) {
			return m.find(rmn_code[current_index] + std::string{ rmn_code[new_index] });
		}
		return m.end();
	}
	void increment(unsigned& index);
}