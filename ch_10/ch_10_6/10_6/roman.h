#pragma once
#include <string>
class Roman_int {
	static constexpr int repeat_limit = 3;
public:
	class Invalid {
	public:
		Invalid(const std::string& err) :error_message{ err } {}
		std::string what() { return error_message; }
	private:
		std::string error_message;
	};
	class Parse_error {
	public:
		Parse_error(const std::string& err) :error_message{ err } {}
		std::string what() { return error_message; }
	private:
		std::string error_message;
	};
	Roman_int();
	Roman_int(const std::string& letters);
	int as_int() const;
	std::string as_string() const;
private:
	std::string roman_code;
	int value;
};
std::ostream& operator<< (std::ostream& os, const Roman_int& r);
std::istream& operator>>(std::istream& is, Roman_int& r);
Roman_int operator +(const Roman_int& left, const Roman_int& right);
Roman_int operator -(const Roman_int& left, const Roman_int& right);
Roman_int operator *(const Roman_int& left, const Roman_int& right);
Roman_int operator /(const Roman_int& left, const Roman_int& right);