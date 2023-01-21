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
	class Invalid {
	public:
		Invalid(const std::string& err) :error_message{ err } {}
		std::string what() { return error_message; }
	private:
		std::string error_message;
	};
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
	Util::check_stream(std::cin, print, "oops couldn't find the terminating character");
	switch (c) {
	case '+':
	case '-':
	case '=':
	case ';':
	case '(':
	case ')':
		return Token(c)
			//case '*':
			//case '$':
			//case '/':
			//case '%':
			;
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
		throw Token_gen::Token::Invalid{ "No numbers. Roman ints only please...\n" };
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
				throw Token::Invalid{ "invalid token..." };
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
			throw Token::Invalid{ s + " is invalid..." };
		}
		else {
			std::cin.unget();
		}
		if (!isspace(c)) {
			Roman_int r;
			std::cin >> r;
			return Token(r);
		}
	}
}
//Roman_int expression(Token_stream& ts);
void Token_stream::ignore(char c) {	// ignores print characters ';'
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	std::cout << "Press; to continue...\n";
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
		Roman_int x = { "iiii" };
		Roman_int y = { "" };
		Roman_int z = x + y;
		std::cout << prompt << " ";
		Token t = ts.get();
		while (t.kind == print) t = ts.get();
		if (t.kind == quit) return;
		ts.unget(t);
		//std::cout << expression(ts) << std::endl;
	}
	catch (std::exception& e) {
		std::cerr << e.what() << "\n";
		clean_up_mess(ts);
	}
	catch (Roman_int::Parse_error& e) {
		std::cerr << e.what() << "\n";
		clean_up_mess(ts);
	}
	catch (Roman_int::Invalid& e) {
		std::cerr << e.what() << "\n";
		clean_up_mess(ts);
	}
	catch (Token::Invalid& e) {
		std::cerr << e.what() << "\n";
		clean_up_mess(ts);
	}
}
//Roman_int expression(Token_stream& ts) {
//	Roman_int left = term(ts);
//	Token t2 = ts.get();
//	switch (t2.kind) {
//	case '+':
//		return left + term(ts);
//	case '-':
//		return left - term(ts);
//	default:
//		break;
//	}
//}
//Roman_int term(Token_stream& ts) {
//	return Roman_int{};
//}
//Roman_int primary(Token_stream& ts) {
//	return Roman_int{};
//}
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