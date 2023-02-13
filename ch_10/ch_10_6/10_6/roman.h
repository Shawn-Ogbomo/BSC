#pragma once
#include <string>
class Roman_int {
	static constexpr int repeat_limit = 3;
public:
	class Invalid {
	public:
		explicit Invalid(const std::string& err) :error_message{ err } {}
		std::string what() const { return error_message; }
	private:
		std::string error_message;
	};
	class Parse_error {
	public:
		explicit Parse_error(const std::string& err) :error_message{ err } {}
		std::string what() const { return error_message; }
	private:
		std::string error_message;
	};
	Roman_int();
	explicit Roman_int(const std::string& letters);
	int as_int() const;
	std::string as_string() const;
private:
	std::string roman_code;
	int value{};
};
std::string integer_to_roman_code(int val);
std::ostream& operator<< (std::ostream& os, const Roman_int& r);
std::istream& operator>>(std::istream& is, Roman_int& r);
Roman_int operator +(const Roman_int& left, const Roman_int& right);
Roman_int operator -(const Roman_int& left, const Roman_int& right);
Roman_int operator *(const Roman_int& left, const Roman_int& right);
Roman_int operator /(const Roman_int& left, const Roman_int& right);
Roman_int operator ^(const Roman_int& left, const Roman_int& right);
Roman_int operator %(const Roman_int& left, const Roman_int& right);
