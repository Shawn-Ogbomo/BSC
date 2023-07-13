#pragma once
#include <string_view>
#include <string>
#include <map>

namespace Util {
	void find_duplicates(std::string_view target_string, char c);

	void repeats(const std::string_view s, char c, unsigned pos);	//RETURNS TRUE IF C REPEATS MORE THAN 3 TIMES IN SUCCESSION

	void increment(const std::map<std::string, int>& map, const std::map<std::string, int>::const_iterator it, unsigned& index);

	//BUILDS A NEW CASE
	std::map<std::string, int>::const_iterator lookup(const std::map <std::string, int>& m, std::string_view rmn_code, int current_index, int new_index);

	//CALCULATES VALUE OF ROMAN CODE
	void sum(const std::map<std::string, int>::const_iterator it1_new_case
		, const std::map<std::string, int>::const_iterator it2_next_new_case
		, const std::map<std::string, int>::const_iterator it3_next
		, const std::map<std::string, int>::const_iterator it4_prev
		, const std::map<std::string, int>& map, int& val, char c);
}