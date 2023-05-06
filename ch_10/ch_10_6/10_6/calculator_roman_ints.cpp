//Shawn Ogbomo
// Sun Jan 15 2023
//Simple calculator v1
//revision history
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
#include <algorithm>
#include <optional>
#include <cctype>
#include <vector>
#include <cmath>
#include "roman.h"
#include "token.h"

class Invalid {};

struct Token {
	Token() = default;
	explicit Token(char c) :kind{ c } {}
	explicit Token(const std::string& name)
		: kind{ '~' },
		name{ name } {}
	explicit Token(const Roman_int& r) : kind{ 'r' }, v_rmn{ r } {}
	char kind{};
	std::string name;
	Roman_int v_rmn{};
};

class Token_stream {
public:
	explicit Token_stream(std::istream const&) {}
	Token get();
	void unget(Token const& t) {
		if (full) {
			throw  std::runtime_error{ "cannot put token into full stream...\n" };
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
const char roman_numeral = 'r';
constexpr std::string_view constant = "const";
constexpr std::string_view ex_key = "exit";

std::optional<Roman_int> is_rmn(const std::string& target) {
	try {
		return Roman_int{ target };
	}
	catch (std::runtime_error) {
		return std::nullopt;
	}
}

Token Token_stream::get() {
	if (full) {
		full = false;
		return buffer;
	}
	char c;
	std::cin.get(c);
	if (std::cin.eof()) {
		throw Invalid{};
	}
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
		throw  std::runtime_error{ "Roman numerals only." };
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
				std::cout << "\nCalculator application...\n\n"
					<< "This calculator contains the functions of a basic calculator. \nModulo, exponent, and square root functions are also included.\n"
					<< "The calculator is also capable of creating variables and constants.\n" << "\nFunctions...\n" << "$ = sqrt\nenter-key = print instead of '='\nq-key to quit or type exit to quit\n\n# variable declaration format\n#shawn=xix or space one space after #key\n\n" <<
					"const declaration format \nconst shawn=xix\n" <<
					"h key to display instructions...\n";
				throw  std::runtime_error{ "\nrestarting..." };
			}
		}

		std::cin.unget();
		std::string s;
		while (std::cin.get(c) && (isalpha(c) || isdigit(c) || c == underscore)) {
			s += c;
		}

		std::cin.unget();
		if (s.empty() || s.front() == underscore) {
			throw  std::runtime_error{ std::string{c} + " is invalid.." };
		}

		if (auto const rmn_object = is_rmn(s)) {
			return Token(rmn_object.value());
		}

		if (s == ex_key) {
			return Token(quit);
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
	Variable() = default;
	explicit  Variable(const std::string& name, const Roman_int& val, bool qualifier = false)
		:n{ name },
		v{ val },
		state{ qualifier } {}
	Roman_int value()const { return v; }
	std::string name() const { return n; }
	bool is_const() const { return state; }
	void set_value(const Roman_int& val) {
		v = val;
	}
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
	catch (std::exception& e) {
		std::cerr << e.what() << "\n";
		clean_up_mess(ts);
	}
}

class Symbol_table {
public:
	static Roman_int declare(Token_stream& ts, Token& t) {
		Token t2 = ts.get();
		if (t2.kind == print) {
			t2 = ts.get();
		}

		if (t2.kind != name) {
			throw  std::runtime_error{ "invalid token: " + std::string{t2.kind} + " expected a name" };
		}

		if (Token t3 = ts.get(); t3.kind != assignment) {
			throw  std::runtime_error{ "invalid token: " + std::string{t3.kind} + " expected " + assignment };
		}

		Roman_int rmn_numeral = expression(ts);
		Variable v = (t.kind == let ? Variable{ t2.name, rmn_numeral } : Variable{ t2.name, rmn_numeral, true });

		if (Symbol_table::is_declared(t2.name)) {
			throw  std::runtime_error{ t2.name + std::string{" is already declared\n"} };
		}
		var_table.push_back(v);
		return v.value();
	}

	static bool is_declared(const std::string& variable_name) {
		return std::any_of(var_table.begin(), var_table.end(), [&variable_name](Variable const& v) {return v.name() == variable_name; });
	}

	static Roman_int value(const std::string& variable_name) {
		if (auto found = std::find_if(var_table.begin(), var_table.end(), [&variable_name](Variable const& v) { return v.name() == variable_name; });
			found != std::end(var_table)) {
			return found->value();
		}
		throw  std::runtime_error{ std::string{"The variable: " + variable_name + " does not exist..."} };
	}

	static void update_value(const std::string& variable_name, const Roman_int& new_value) {
		if (auto found = std::find_if(var_table.begin(), var_table.end(), [&variable_name](Variable const& v) { return v.name() == variable_name; });
			found != std::end(var_table)) {
			if (found->is_const()) {
				std::cerr << variable_name << ": is marked constant. Unmodifiable...\n";
				return;
			}
			found->set_value(new_value);
			return;
		}
		std::cerr << "The variable: " << variable_name << " does not exist...";
	}

private:
	static inline std::vector<Variable> var_table;
};

Roman_int statement(Token_stream& ts) {
	Token t = ts.get();
	if (t.kind == let || t.kind == permanent) {
		return Symbol_table::declare(ts, t);
	}

	if (t.kind == name && Symbol_table::is_declared(t.name)) {
		Token t2 = ts.get();
		if (t2.kind == print) {
			return Symbol_table::value(t.name);
		}

		if (t2.kind == assignment) {
			Symbol_table::update_value(t.name, expression(ts));
			return Symbol_table::value(t.name);
		}
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
			throw  std::runtime_error{ "')' expected\n" };
		}
		while (std::cin.peek() == '(') {
			t = ts.get();
			left = left * expression(ts);
			t = ts.get();
			if (t.kind != ')') {
				throw  std::runtime_error{ "')' expected\n" };
			}
		}
		return left;
	}
	case roman_numeral:
		return t.v_rmn;
	case name:
		return Symbol_table::value(t.name);
	default:
		throw  std::runtime_error{ "\nExpected term..." };
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
		std::cerr << "Something went wrong...\n";
		return 2;
	}
}