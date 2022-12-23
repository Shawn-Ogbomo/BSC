#pragma once
namespace Utils {
	class Invalid {};
	int get_int();
	int get_int(int low, int high, const std::string& greeting, const std::string& sorry);
	void skip_to_int();
};