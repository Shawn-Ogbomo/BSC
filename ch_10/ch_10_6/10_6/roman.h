#pragma once
#include <string>
#include "token.h"
class Roman_int {
public:
	class Invalid {};
	Roman_int();
	Roman_int(const std::string& symbols);
	int as_int() const;
	std::string as_string() const;
private:
	std::string roman_code;
	int value;
	//int expression(Token_stream& ts);
};
std::ostream& operator<< (std::ostream& os, const Roman_int& r);
//std::istream& operator >> (std::istream& is, Roman_int& r);