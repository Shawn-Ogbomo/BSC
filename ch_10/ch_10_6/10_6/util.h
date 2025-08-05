#ifndef UTIL_H
#define UTIL_H

#include <map>
#include <string>
#include <string_view>

namespace Util {
	auto find_duplicates(std::string_view target_string, char c) -> void;

	//RETURNS TRUE IF C REPEATS MORE THAN 3 TIMES IN SUCCESSION
	auto repeats(const std::string_view s, char c, unsigned pos) -> void;

	auto increment(const std::map<std::string, int>& map, const std::map<std::string, int>::const_iterator it, std::size_t& index) -> void;

	//BUILDS A NEW CASE
	auto build_new_case(const std::map <std::string, int>& m, std::string_view rmn_code, int current_index, int new_index) -> std::map<std::string, int>::const_iterator;

	//FINDS NEXT AND PREVIOUS
	auto next_or_previous(const std::map<std::string, int>& m, std::string_view rmn_code, std::size_t new_index) -> std::map<std::string, int>::const_iterator;

	//CALCULATES VALUE OF ROMAN CODE
	auto sum(const std::map<std::string, int>::const_iterator it1_new_case
		, const std::map<std::string, int>::const_iterator it2_next_new_case
		, const std::map<std::string, int>::const_iterator it3_next
		, const std::map<std::string, int>::const_iterator it4_prev
		, const std::map<std::string, int>& map, int& val, char c) -> void;

	auto parse_rmn_by_placevalue(std::string& result, const std::map<std::string, int>& map, char rmn_letter, int& val, char next_rmn_letter = 0) -> void;

	//FORMATS THE STRING TO START WITH UPPERCASE AND EACH SUBSEQUENT CHARACTER TO LOWERCASE
	auto format_string(std::string& target_string) -> void;

	//SKIPS BAD INPUT
	auto skip_input(std::istream& is, char terminator) -> void;

	//CHECKS STREAM STATE
	auto check_stream(std::istream& is, const std::string& message, const std::string& message2 = "") -> void;
}
#endif // UTIL_H