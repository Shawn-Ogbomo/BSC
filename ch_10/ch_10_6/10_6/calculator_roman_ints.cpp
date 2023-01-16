//Shawn Ogbomo
// Sun Jan 15 2023
//Simple calculator v1
//revision history
// works on Roman_ints only
//This program implements a basic expression calculator.
//Input from cin; output to cout.
//The grammar for input is:
//Expression:
//Term
//Expression "+" Term
//Expression "-" Term
//
//
//Term :
//primary
//Term $(sqrt)
//Term "^" Primary
//Term "*" Primary
//Term "/" Primary
//Term "%" Primary
//
//
//Primary :
//Roman numeral
//"(" Expression ")"
//
//Roman numeral :
//<string, int>
//<char, int>
#include <iostream>
#include "roman.h"
#include "token.h"
struct Token {
	Token() :kind{}, value{}, letters{} {}
	Token(char c) :kind{ c }, letters{}, value{} {}
	Token(const Roman_int& r) :letters{ r.as_string() }, value{ r.as_int() }, kind{} {}
	char kind;
	std::string letters;
	int value;
};
class Token_stream {
public:
	class Invalid {};
	Token_stream(std::istream&) :full{ false }, buffer{}{}
	Token get();
	void unget(Token t) {
		if (full) {
			std::cerr << "cannot put token into full stream...\n";
			throw Token_stream::Invalid{};
		}
		buffer = t;
		full = true;
	}
	void ignore(char c);
private:
	bool full;
	Token buffer;
};
constexpr char print = ';';

Token Token_stream::get() {
	if (full) {
		full = false;
		return buffer;
	}
	char c{};
	std::cin >> c;
	switch (c) {
	case '+':
	case '-':
	case '*':
	case '$':
	case '/':
	case '%':
	case '(':
	case ')':
		return Token(c);
	default:
		if (isalpha(c)) {
			std::cin.unget();
			Roman_int r;
			std::cin >> r;
			return Token(r);
		}
		std::cerr << "\nBad token: " << c << "\n";
		throw std::runtime_error("Invalid input...\nPress ; to continue");
	}
}
Roman_int expression(Token_stream& ts);
void Token_stream::ignore(char c)																												// ignores print characters ';'
{
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;
	char ch;
	while (std::cin >> ch)
		if (ch == c) return;
}
void clean_up_mess(Token_stream& ts)
{
	ts.ignore(print);
}
void calculate(Token_stream& ts) {
	try {
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << "\n";
		clean_up_mess(ts);
	}
}
int main() {
	try {
		Token_stream ts{ std::cin };
		calculate(ts);
	}

	catch (const std::exception& e) {
		std::cerr << e.what() << "\n";
		return 1;
	}
	catch (...) {
		std::cerr << "Something went wrong...\n";
		return 2;
	}
}
Roman_int expression(Token_stream& ts) {
	return Roman_int{};
}