//Shawn Ogbomo
// Sun Jan 15 2023
//Simple calculator v1
//revision history
//added function roman_letter() to prevent putting multiple characters back into the input stream
//added end_of_loop() to handle stream fail, eof , and bad
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
#include <cctype>
#include <vector>
#include <algorithm>
#include "roman.h"
#include "token.h"
#include "util.h"
struct Token {
	class Invalid {};
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
const char print = ';';
const char  quit = 'q';
const char  help = 'h';
const std::string ex_key = "exit";
bool roman_letter(char c) {
	static std::vector<char>valids = { 'I','V','X','L','C','D','M','i','v','l','c','d','m' };
	auto result1 = std::find(begin(valids), end(valids), c);
	if (result1 != std::end(valids)) {
		return true;
	}
	return false;
}
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
	case '=':
	case ';':

		//case '*':
		//case '$':
		//case '/':
		//case '%':
		//case '(':
		//case ')':
		return Token(c);
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case '.':
	{
		std::cin.unget();
		double d{};
		std::cin >> d;
		std::cerr << "oops " << d << " will not work with this calculator. \nRoman numerals only.\n";
		throw std::runtime_error("Press ; to continue");
	}
	default:
		if (isalpha(c) && std::cin.peek() == '\n') {
			if (c == quit) {
				return Token(quit);
			}
			if (c == help) {
				std::cout << "Calculator application...\n\n"
					<< "This calculator contains the functions of a basic calculator. \nModulo, exponent, and square root functions are also included...\n";
				//<< "The calculator is also capable of creating variables and constants; calculations are possible on such expressions.\n"
					//<< "Functions... \n\n" << "$ = sqrt\nenter-key = print instead of '='\nq-key to quit or type exit to quit\n#to declare a variable and #const to declare a constant\nh key to display instructions...\n";
				throw std::runtime_error("Press ; to continue");
			}
			std::cin.unget();
		}
		else if (isalpha(c) && (!roman_letter(std::cin.peek()))) {
			std::cin.unget();
			std::string s;
			while (std::cin.get(c) && !isspace(c)) {
				s += c;
			}
			std::cin.unget();
			if (s == ex_key) {
				return Token(quit);
			}
			std::cerr << s << " is invalid...\n";
			throw std::runtime_error("Invalid input...\nPress ; to continue");
		}
		else {
			std::cin.unget();
		}
		Util::end_of_loop(std::cin, print, "oops couldn't find the terminating character");
		if (!isspace(c)) {					//
			Roman_int r;
			std::cin >> r;
			return Token(r);
		}
	}
}
Roman_int expression(Token_stream& ts);
void Token_stream::ignore(char c) {	// ignores print characters ';'
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;
	char ch;
	while (std::cin >> ch)
		if (ch == c) return;
}
void clean_up_mess(Token_stream& ts) {
	ts.ignore(print);
}
const char prompt = '>';
const char result = '=';
void calculate(Token_stream& ts) {
	while (true)try {
		std::cout << prompt << " ";
		Token t = ts.get();
		while (t.kind == print) t = ts.get();
		if (t.kind == quit) return;
		ts.unget(t);
		std::cout << expression(ts) << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << "\n";
		clean_up_mess(ts);
	}
}
Roman_int expression(Token_stream& ts) {
	return Roman_int{};
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
		std::cerr << "Something went wrong...";
		return 2;
	}
}