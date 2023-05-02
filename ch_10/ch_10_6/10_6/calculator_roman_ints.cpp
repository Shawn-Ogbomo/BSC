//Shawn Ogbomo
// Sun Jan 15 2023
//Simple calculator v1
//revision history
//added end_of_loop() to handle stream fail, eof , and bad
// works on Roman numerals
// computations resulting in fractional values yield erroneous results
// inputting the character 'x' sends output to file 'X' represents the number 10
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
#include <iostream>
#include <cctype>
#include <vector>
#include <algorithm>
#include <cmath>
#include "roman.h"
#include "token.h"
#include "util.h"

struct Token {
	class Invalid {
	public:
		explicit Invalid(const std::string& err) :error_message{ err } {}
		std::string what() const { return error_message; }
	private:
		std::string error_message;
	};
	Token() = default;
	explicit Token(char c) :kind{ c } {}
	explicit Token(const std::string& name)
		: kind{ '~' },
		name{ name } {}
	explicit Token(const Roman_int& r) : kind{ 'r' }, rmn_letters{ r.as_string() }, value{ r.as_int() } {}
	char kind{};
	std::string name;
	std::string rmn_letters;
	int value{};
};

class Token_stream {
public:
	class Invalid {};
	explicit Token_stream(std::istream const&) {}
	Token get();
	void unget(Token const& t) {
		if (full) {
			std::cerr << "cannot put token into full stream...\n";
			throw Token_stream::Invalid{};
		}
		buffer = t;
		full = true;
	}
	void ignore(char c);
private:
	bool full{};
	Token buffer{};
};

const char print = ';';
const char  quit = 'q';
const char  help = 'h';
const char let = '#';
const char name = '~';
const char assignment = '=';
const char underscore = '_';
const char permanent = 'k';
const std::string constant = "const";
const char roman_numeral = 'r';
const std::string ex_key = "exit";
const std::string nulla = "nulla";

bool is_rmn(const std::string& target, Token_stream& ts) {
	try {
		Roman_int r{ target };
		ts.unget(static_cast<Token>(r));
		return true;
	}
	catch (Token_gen::Token::Invalid) {
		return false;
	}
	catch (Roman_int::Parse_error) {
		return false;
	}
}

Token Token_stream::get() {
	if (full) {
		full = false;
		return buffer;
	}
	char c;
	std::cin.get(c);
	Util::check_stream(std::cin, print, "oops couldn't find the terminating character");
	switch (c) {
	case '+':
	case '-':
	case '*':
	case '/':
	case '=':
	case ';':
	case '(':
	case ')':
	case '$':
	case '%':
	case '^':
	case '#':
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
		throw Token::Invalid{ "Roman numerals only." };
	}
	default:
		if (isspace(c)) {
			return Token(print);
		}
		if (isalpha(c) && std::cin.peek() == '\n') {
			if (c == quit) {
				return Token(quit);
			}
			if (c == help) {
				std::cout << "Calculator application...\n\n"
					<< "This calculator contains the functions of a basic calculator. \nModulo, exponent, and square root functions are also included.\n"
					<< "The calculator is also capable of creating variables and constants.\n" << "\nFunctions...\n" << "$ = sqrt\nenter-key = print instead of '='\nq-key to quit or type exit to quit\n\n# variable declaration format\n#shawn=xix\n\n" <<
					"const declaration format \nconst shawn=xix\n" <<
					"h key to display instructions...\n";
				throw Token::Invalid{ "\nrestarting..." };
			}
		}

		std::cin.unget();
		std::string s;
		while (std::cin.get(c) && (isalpha(c) || isdigit(c) || c == underscore)) {
			s += c;
		}
		std::cin.unget();
		if (s.empty() || s.front() == underscore) {
			throw Token::Invalid{ std::string{c} + " is invalid.." };
		}
		if (is_rmn(s, *this)) {
			return get();	//return the stored token
		}

		if (s == ex_key) {
			return Token(quit);
		}
		if (s == nulla) {
			return Token(static_cast<Roman_int>(s));
		}
		if (s == constant) {
			return Token(permanent);
		}
		std::string internal_name = s;
		return Token(internal_name);
	}
}

Roman_int statement(Token_stream& ts);
Roman_int expression(Token_stream& ts);
void Token_stream::ignore(char c) {	// ignores print characters ';'
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	std::cout << "Press; to continue...\n";
	full = false;
	char ch;
	while (std::cin >> ch) {
		if (ch == c) {
			return;
		}
	}
}

void clean_up_mess(Token_stream& ts) {
	ts.ignore(print);
}

const char prompt = '>';
const char result = '=';

class Variable {
public:
	class Double_declaration {
	public:
		explicit Double_declaration(const std::string& err) :error_message{ err } {}
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

	Variable() = default;
	explicit  Variable(const std::string& name, const Roman_int& val, bool qualifier = false)
		:n{ name },
		v{ val },
		state{ qualifier } {}
	Roman_int value() const { return v; }
	std::string name() const { return n; }
	bool is_const() const { return state; }
private:
	std::string n;
	Roman_int v;
	bool state{};
};

void calculate(Token_stream& ts) {
	while (true)try {
		std::cout << prompt << " ";
		Token t = ts.get();
		while (t.kind == print) t = ts.get();
		if (t.kind == quit) return;
		ts.unget(t);
		std::cout << result << " " << statement(ts) << std::endl;
	}
	catch (std::length_error& e) {
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
	catch (Token_gen::Token::Invalid& e) {
		std::cerr << e.what() << "\n";
		clean_up_mess(ts);
	}
	catch (Variable::Double_declaration& e) {
		std::cerr << e.what() << "\n";
		clean_up_mess(ts);
	}
}

std::vector<Variable> variables;
struct Symbol_table {
public:
	static bool is_declared(const std::string& variable_name) {
		return std::any_of(variables.begin(), variables.end(), [&variable_name](Variable const& v) {return v.name() == variable_name; });
	}

	static Roman_int value(const std::string& variable_name) {
		if (auto found = std::find_if(variables.begin(), variables.end(), [&variable_name](Variable const& v) { return v.name() == variable_name; });
			found != std::end(variables)) {
			return found->value();
		}
		throw Roman_int::Invalid{ std::string{"The variable " + variable_name + " does not exist..."} };
	}

	static void update_value(const std::string& variable_name, const Roman_int& new_value) {
		if (auto found = std::find_if(variables.begin(), variables.end(), [&variable_name](Variable const& v) { return v.name() == variable_name; });
			found != std::end(variables)) {
			found->value() = new_value;
		}
		throw Roman_int::Invalid{ std::string{"The variable " + variable_name + " does not exist..."} };
	}
};

Roman_int statement(Token_stream& ts) {
	Token t = ts.get();
	if (t.kind == let || t.kind == permanent) {
		Token t2 = ts.get();
		if (t2.kind == print) {
			Util::clear_white_space();
			t2 = ts.get();
		}
		if (t2.kind != name) {
			throw Token::Invalid{ "invalid token: " + std::string{t2.kind} + " expected a name" };
		}
		Token t3 = ts.get();
		if (t3.kind == print) {
			Util::clear_white_space();
			t3 = ts.get();
		}
		if (t3.kind != assignment) {
			throw Token::Invalid{ "invalid token: " + std::string{t3.kind} + " expected " + assignment };
		}

		t3 = ts.get();
		if (t3.kind == print) {
			Util::clear_white_space();
		}
		else {
			ts.unget(t3);
		}

		Roman_int rmn_numeral = expression(ts);
		Variable v = (t.kind == let ? Variable{ t2.name, rmn_numeral } : Variable{ t2.name, rmn_numeral, true });

		if (Symbol_table::is_declared(t2.name)) {
			throw Variable::Double_declaration{ t2.name + std::string{" is already declared\n"} };
		}

		variables.push_back(v);
		t = ts.get();										//get next token
		return v.value();
	}

	if (t.kind == name && Symbol_table::is_declared(t.name)) {
		Token t2 = ts.get();
		if (t2.kind == print) {
			Util::clear_white_space();
			if (!std::cin.peek()) {
				return Symbol_table::value(t.name);
			}
			else {
				t2 = ts.get();
			}
		}

		if (t2.kind == assignment) {
			Util::clear_white_space();
			Token t3 = ts.get();
			if (t3.kind == roman_numeral) {
				Symbol_table::update_value(t.name, static_cast<Roman_int>(t3.rmn_letters));
				return Symbol_table::value(t.name);
			}
		}
		throw Variable::Parse_error{ "Unable to parse a variable...\n" };
	}

	ts.unget(t);
	return expression(ts);								//check for roman_int
}

Roman_int primary(Token_stream& ts) {
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{
		Roman_int left = expression(ts);
		t = ts.get();
		if (t.kind != ')') {
			throw Roman_int::Parse_error{ "')' expected\n" };
		}
		while (std::cin.peek() == '(') {
			t = ts.get();
			left = left * expression(ts);
			t = ts.get();
			if (t.kind != ')') {
				throw Roman_int::Parse_error{ "')' expected\n" };
			}
		}
		return left;
	}
	case roman_numeral:
		return Roman_int{ t.rmn_letters };
	default:
		throw Roman_int::Parse_error{ "\nExpected term..." };
	}
}

Roman_int term(Token_stream& ts) {
	Roman_int left = primary(ts);
	Token t2 = ts.get();
	while (true) {
		switch (t2.kind) {
		case '$':
		{
			left = Roman_int{ integer_to_roman_code(std::sqrt(left.as_int())) };
			t2 = ts.get();
			break;
		}
		case'^':
		{
			left = left ^ primary(ts);
			t2 = ts.get();
			break;
		}
		case '/':
		{
			left = left / primary(ts);
			t2 = ts.get();
			break;
		}
		case '*':
		{
			left = left * primary(ts);
			t2 = ts.get();
			break;
		}
		case '%':
		{
			left = left % primary(ts);
			t2 = ts.get();
			break;
		}
		default:
			ts.unget(t2);
			return left;
		}
	}
}

Roman_int expression(Token_stream& ts) {
	Roman_int left = term(ts);
	Token t2 = ts.get();
	while (true) {
		switch (t2.kind) {
		case '+':
			left = left + term(ts);
			t2 = ts.get();
			break;
		case '-':
			left = left - term(ts);
			t2 = ts.get();
			break;
		default:
			ts.unget(t2);
			return left;
		}
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
		std::cerr << "Something went wrong...";
		return 2;
	}
}