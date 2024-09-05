#ifndef ROMAN_H
#define ROMAN_H

#include <string>
#include <string_view>

class Roman_int {
	static constexpr int repeat_limit = 3;
public:
	Roman_int();
	explicit Roman_int(const std::string& letters);

	friend auto operator >> (std::istream& is, Roman_int& r)->std::istream&;
	friend auto operator<< (std::ostream& os, const Roman_int& r)->std::ostream&;
	friend auto operator +(const Roman_int& left, const Roman_int& right)->Roman_int;
	friend auto operator -(const Roman_int& left, const Roman_int& right)->Roman_int;
	friend auto operator *(const Roman_int& left, const Roman_int& right)->Roman_int;
	friend auto operator /(const Roman_int& left, const Roman_int& right)->Roman_int;
	friend auto operator ^(const Roman_int& left, const Roman_int& right)->Roman_int;
	friend auto operator %(const Roman_int& left, const Roman_int& right)->Roman_int;

	auto as_int() const -> const int&;
	auto as_string() const->std::string_view;
private:
	std::string roman_code{ "nulla" };
	int value{};
};

std::string integer_to_roman_code(int val);

#endif // ROMAN_H