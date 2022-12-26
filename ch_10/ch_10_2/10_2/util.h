#pragma once
namespace Utils {
	class Invalid {};
	int get_int(std::istream& is = std::cin);
	int get_int(int low, int high, const std::string& greeting, const std::string& sorry);
	void skip_to_int(char term, std::istream& is = std::cin);
};