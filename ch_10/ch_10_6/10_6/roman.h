#pragma once
#include <string>
class Roman_int {
	static constexpr int repeat_limit = 3;
public:
	class Invalid {};
	Roman_int();
	Roman_int(const std::string& letters);
	Roman_int(const char letter);
	int as_int() const;
	std::string as_string() const;
private:
	std::string roman_code;
	char roman_character;
	int value;
};
std::ostream& operator<< (std::ostream& os, const Roman_int& r);
std::istream& operator>>(std::istream& is, Roman_int& r);