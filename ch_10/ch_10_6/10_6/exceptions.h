#pragma once
#include <string>

class Bad_input {
public:
	explicit Bad_input(const std::string& err) :error_message{ err } {}
	const std::string& what() const { return error_message; }
private:
	std::string error_message;
};

class Invalid {
public:
	explicit Invalid(const std::string& err) :error_message{ err } {}
	const std::string& what() const { return error_message; }
private:
	std::string error_message;
};
