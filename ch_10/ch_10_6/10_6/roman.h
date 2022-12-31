#pragma once
#include <string>
class Roman_int {
	static constexpr int max_sz = 9;
	static constexpr int repeat_limit = 4;
public:
	class Invalid {};
	Roman_int();
	Roman_int(const std::string& symbols);
	int as_int() const;
	std::string as_symbols() const;
private:
	std::string roman_code;
	int value;
};
std::ostream& operator << (std::ostream& os, const Roman_int& r);
//std::istream& operator >> (std::istream& is, Roman_int& r);