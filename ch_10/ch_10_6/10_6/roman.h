#pragma once
#include <string>
class Roman_int {
	static const int max_sz = 4;
public:
	class Invalid {};
	Roman_int();
	Roman_int(const std::string& symbols);
	int as_int() const;
private:
	std::string roman_code;
	int value;
};