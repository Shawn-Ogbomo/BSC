#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>
#include <string>

class Terminate {
public:
	explicit Terminate(const std::string& err) :error_message{ err } {}
	const std::string& what() const { return error_message; }
private:
	std::string error_message;
};
#endif // EXCEPTIONS_H