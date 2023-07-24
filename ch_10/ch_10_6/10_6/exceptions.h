#pragma once
#include <iostream>
#include <string>

class Invalid {
public:
	explicit Invalid(const std::string& err) :error_message{ err } {}
	const std::string& what() const { return error_message; }
private:
	std::string error_message;
};

class Invalid_file {
public:
	explicit Invalid_file(const std::string& err) :error_message{ err } {}
	const std::string& what() const { return error_message; }
private:
	std::string error_message;
};
