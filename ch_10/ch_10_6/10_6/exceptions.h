#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>
#include <string>

class Terminate : public std::runtime_error {
public:
	using std::runtime_error::runtime_error;
};

class Invalid_format : public std::runtime_error {
	using std::runtime_error::runtime_error;
};
#endif // EXCEPTIONS_H