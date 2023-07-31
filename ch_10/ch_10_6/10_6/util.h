#ifndef UTIL_H
#define UTIL_H

#include <string_view>
#include <string>
#include <map>

namespace Util {
	void find_duplicates(std::string_view target_string, char c);

	//RETURNS TRUE IF C REPEATS MORE THAN 3 TIMES IN SUCCESSION
	void repeats(const std::string_view s, char c, unsigned pos);

	void increment(const std::map<std::string, int>& map, const std::map<std::string, int>::const_iterator it, unsigned& index);

	//BUILDS A NEW CASE
	std::map<std::string, int>::const_iterator build_new_case(const std::map <std::string, int>& m, std::string_view rmn_code, int current_index, int new_index);

	//FINDS NEXT AND PREVIOUS
	std::map<std::string, int>::const_iterator next_or_previous(const std::map<std::string, int>& m, std::string_view rmn_code, int new_index);

	//CALCULATES VALUE OF ROMAN CODE
	void sum(const std::map<std::string, int>::const_iterator it1_new_case
		, const std::map<std::string, int>::const_iterator it2_next_new_case
		, const std::map<std::string, int>::const_iterator it3_next
		, const std::map<std::string, int>::const_iterator it4_prev
		, const std::map<std::string, int>& map, int& val, char c);

	void parse_rmn_by_placevalue(std::string& result, const std::map<std::string, int>& map, char rmn_letter, int& val, char next_rmn_letter = 0);

	//FORMATS THE STRING TO START WITH UPPERCASE AND EACH SUBSEQUENT CHARACTER TO LOWERCASE
	void format_string(std::string& target_string);

	//SKIPS BAD INPUT
	void skip_input(std::istream& is, char terminator);

	//CHECKS STREAM STATE
	void check_stream(std::istream& is, const std::string& message, const std::string& message2 = "");
}
#endif // UTIL_H