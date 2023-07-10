#pragma once
#include <string>
class Roman_int {
	static constexpr int repeat_limit = 3;
public:
	Roman_int();
	explicit Roman_int(const std::string& letters);
	const int& as_int() const;
	std::string_view as_string() const;
private:
	std::string roman_code = "nulla";
	int value{};
};
std::string integer_to_roman_code(int val);
std::ostream& operator<< (std::ostream& os, const
	Roman_int& r);
std::istream& operator >> (std::istream& is, Roman_int& r);
Roman_int operator +(const Roman_int& left, const Roman_int& right);
Roman_int operator -(const Roman_int& left, const Roman_int& right);
Roman_int operator *(const Roman_int& left, const Roman_int& right);
Roman_int operator /(const Roman_int& left, const Roman_int& right);
Roman_int operator ^(const Roman_int& left, const Roman_int& right);
Roman_int operator %(const Roman_int& left, const Roman_int& right);