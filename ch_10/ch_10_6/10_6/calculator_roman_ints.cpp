//Shawn Ogbomo
// Sun Aug 2 2023
//Simple calculator v1
//revision history
// works on Roman numerals
// computations resulting in fractional values yield erroneous results
// inputting the character 'x' takes input from file 'X' represents the number 10
// inputting the character 'y' send output to file
// Roman numerals must be entered in uppercase
// division that results in a fractional value yields erroneous results
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
#include <string_view>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <cmath>
#include "roman.h"
#include "util.h"
#include "exceptions.h"

struct Token {
	Token() = default;
	explicit Token(char c) :kind{ c } {}
	explicit Token(const std::string& name)
		: kind{ '~' },
		name{ name } {}
	explicit Token(const Roman_int& r) : kind{ 'r' }, v_rmn{ r } {}
	char kind{};
	std::string name;
	Roman_int v_rmn;
};

class Token_stream {
public:
	explicit Token_stream(std::istream const&) {}
	Token get(std::istream& is = std::cin, std::ostream & = std::cout);

	void unget(Token const& t) {
		if (full) {
			throw  std::runtime_error{ "cannot put token into full stream..." };
		}
		buffer = t;
		full = true;
	}
	void ignore(char c);
private:
	bool full{};
	Token buffer;
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
const char file = 'x';
const char output_to_file = 'y';
constexpr std::string_view constant = "const";
constexpr std::string_view ex_key = "exit";

//CHECKS FOR NAME,CONST,EXIT, AND ROMAN INT
Token remaining_case(char c, std::istream& is) {
	if (c == name) {
		std::string s;
		while (is.get(c) && c == underscore || isalpha(c) || isdigit(c)) {
			s += c;
		}

		is.unget();

		if (s.empty() || s.front() == underscore || isdigit(s.front())) {
			throw std::runtime_error{ "Invalid name format..." };
		}

		Util::format_string(s);
		return Token(s);
	}

	if (c == 'c' || c == 'e') {
		std::string pattern = "abcdefghijklmnopqrstuvwxyz";
		std::string internal_s;

		is.unget();

		while (is.get(c) && (pattern.find(c) != std::string::npos)) {
			internal_s += c;
		}

		if (internal_s == constant) {
			return Token{ permanent };
		}

		if (internal_s == ex_key) {
			return Token{ quit };
		}

		throw std::runtime_error{ "your input is not const or exit..." };
	}

	is.putback(c);

	Roman_int rmn;
	is >> rmn;

	Util::check_stream(is, "couldn't build a roman int...");

	return Token{ rmn };
}

Token Token_stream::get(std::istream& is, std::ostream& os) {
	if (full) {
		full = false;
		return buffer;
	}
	char c{};
	is.get(c);
	Util::check_stream(is, "exiting...");

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

		if (isalpha(c) && is.peek() == '\n') {
			if (c == quit) {
				return Token(quit);
			}

			if (c == help) {
				os << "\nCalculator application...\n\n"
					<< "This calculator contains the functions of a basic calculator. \nModulo, exponent, and square root functions are also included.\n"
					<< "The calculator is also capable of creating variables and constants.\n"
					<< "\nFunctions...\n" << "$ = sqrt\nenter-key = print instead of '='\nq-key to quit or type exit to quit\n\n# variable declaration format\n#~shawn=roman_numeral or one space after or before = key\n\n"
					<< "const declaration format \nconst ~shawn=roman_numeral or const ~shawn =roman_numeral or const ~shawn = roman_numeral\n"
					<< "h key to display instructions...\n"
					<< "y key to send all cerr output and standard output to a file\n";

				throw  std::runtime_error{ "\nrestarting..." };
			}

			if (c == file) {
				return Token{ file };
			}

			if (c == output_to_file) {
				return Token{ output_to_file };
			}
		}

		return remaining_case(c, is);
	}
}

Roman_int statement(Token_stream& ts, std::istream& is = std::cin, std::ostream& os = std::cout);
Roman_int expression(Token_stream& ts, std::istream& is = std::cin);

// ignores print characters ';'
void Token_stream::ignore(char c) {
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
	const Roman_int& value()const { return v; }
	std::string_view name() const { return n; }
	bool is_const() const { return state; }
	void set_value(const Roman_int& val) {
		v = val;
	}
private:
	std::string n;
	Roman_int v;
	bool state{};
};

void file_prompt(std::string& f_name) {
	std::cout << "Enter the name of the file: ";
	std::cin >> f_name;
}

//TAKES INPUT FROM FILE
void from_file(Token_stream& ts, std::ostream& os = std::cout) {
	std::string file_name;
	file_prompt(file_name);
	std::ifstream ifs{ file_name };

	Util::check_stream(ifs, "Oops, the file: " + file_name + " does not exist...", "\nyou pressed ctrl+z\nexiting....");

	while (ifs)try {
		os << prompt << " ";
		Token t = ts.get(ifs);

		while (t.kind == print) {
			if (ifs.peek() == -1) {
				return;
			}
			t = ts.get(ifs);
		}

		ts.unget(t);
		os << result << " " << statement(ts, ifs) << std::endl;
	}
	catch (std::runtime_error& e) {
		os << e.what() << "\n";
		Util::skip_input(ifs, print);
	}
}

void calculate(Token_stream& ts, std::ostream& os = std::cout);

//SEND OUTPUT TO FILE
void to_file(Token_stream& ts, std::ostream& os) {
	std::cout << "press q or type exit to stop sending output to file...\n";

	calculate(ts, os);
}

void calculate(Token_stream& ts, std::ostream& os) {
	while (true)try {
		std::cout << prompt << " ";
		Token t = ts.get(std::cin, os);

		while (t.kind == print) {
			t = ts.get(std::cin, os);
		}

		if (t.kind == quit) {
			return;
		}

		if (t.kind == file) {
			from_file(ts, os);
			std::cout << "Finished reading file contents.\n";
			continue;
		}

		if (t.kind == output_to_file) {
			std::string file_name;	file_prompt(file_name);
			std::ofstream oft{ file_name };

			to_file(ts, oft);
			std::cout << "Finished writing file contents.\n";
			continue;
		}

		ts.unget(t);
		os << result << " " << statement(ts) << std::endl;
	}

	catch (std::exception& e) {
		os << e.what() << "\n";
		clean_up_mess(ts);
	}
}

class Symbol_table {
public:
	static Roman_int declare(Token_stream& ts, const Token& t, std::istream& is = std::cin) {
		Token t2 = ts.get(is);

		if (t2.kind != name) {
			throw  std::runtime_error{ "invalid token: " + std::string{t2.kind} + " expected a name" };
		}

		if (Token t3 = ts.get(is); t3.kind != print) {
			ts.unget(t3);
		}

		if (Token t4 = ts.get(is); t4.kind != assignment) {
			throw  std::runtime_error{ "invalid token: " + std::string{t4.kind} + " expected " + assignment };
		}

		if (Token t5 = ts.get(is); t5.kind != print) {
			ts.unget(t5);
		}

		if (Symbol_table::is_declared(t2.name)) {
			throw  std::runtime_error{ t2.name + std::string{" is already declared\n"} };
		}

		Roman_int rmn_numeral = expression(ts, is);
		Variable v = (t.kind == let ? Variable{ t2.name, rmn_numeral } : Variable{ t2.name, rmn_numeral, true });

		var_table.push_back(v);
		return v.value();
	}

	static bool is_declared(std::string_view variable_name) {
		return std::any_of(var_table.begin(), var_table.end(), [&variable_name](Variable const& v) {return v.name() == variable_name; });
	}

	static Roman_int value(std::string_view variable_name) {
		if (auto found = std::find_if(var_table.begin(), var_table.end(), [&variable_name](Variable const& v) { return v.name() == variable_name; });
			found != std::end(var_table)) {
			return found->value();
		}
		throw  std::runtime_error{ "The variable: " + static_cast<std::string>(variable_name) + " does not exist..." };
	}

	static void update_value(std::string_view variable_name, const Roman_int& new_value, std::ostream& os = std::cout) {
		if (auto found = std::find_if(var_table.begin(), var_table.end(), [&variable_name](Variable const& v) { return v.name() == variable_name; });
			found != std::end(var_table)) {
			if (found->is_const()) {
				os << variable_name << ": is marked constant. Unmodifiable...\n";
				return;
			}
			found->set_value(new_value);
			return;
		}
		os << "The variable: " << variable_name << " does not exist...";
	}

private:
	static inline std::vector<Variable> var_table;
};

Roman_int statement(Token_stream& ts, std::istream& is, std::ostream& os) {
	Token t = ts.get(is);
	if (t.kind == let || t.kind == permanent) {
		return Symbol_table::declare(ts, t, is);
	}

	if (t.kind == name) {
		if (Symbol_table::is_declared(t.name)) {
			Token t2 = ts.get(is);
			if (t2.kind == print) {
				return Symbol_table::value(t.name);
			}

			if (t2.kind == assignment) {
				Symbol_table::update_value(t.name, expression(ts, is), os);
				return Symbol_table::value(t.name);
			}
		}
		throw std::runtime_error{ "The variable: " + t.name + " does not exist...\n" };
	}

	ts.unget(t);
	return expression(ts, is);
}

Roman_int primary(Token_stream& ts, std::istream& is = std::cin) {
	Token t = ts.get(is);
	switch (t.kind) {
	case '(':
	{
		Roman_int left = expression(ts, is);
		t = ts.get(is);
		if (t.kind != ')') {
			throw  std::runtime_error{ "')' expected\n" };
		}
		while (is.peek() == '(') {
			t = ts.get(is);
			left = left * expression(ts, is);
			t = ts.get(is);
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

Roman_int term(Token_stream& ts, std::istream& is = std::cin) {
	Roman_int left = primary(ts, is);
	Token t2 = ts.get(is);
	while (true) {
		switch (t2.kind) {
		case '$':
		{
			left = Roman_int{ integer_to_roman_code(std::sqrt(left.as_int())) };
			t2 = ts.get(is);
			break;
		}
		case '^':
		{
			left = left ^ primary(ts, is);
			t2 = ts.get(is);
			break;
		}
		case '/':
		{
			left = left / primary(ts, is);
			t2 = ts.get(is);
			break;
		}
		case '*':
		{
			left = left * primary(ts, is);
			t2 = ts.get(is);
			break;
		}
		case '%':
		{
			left = left % primary(ts, is);
			t2 = ts.get(is);
			break;
		}
		default:
			ts.unget(t2);
			return left;
		}
	}
}

Roman_int expression(Token_stream& ts, std::istream& is) {
	Roman_int left = term(ts, is);
	Token t2 = ts.get(is);
	while (true) {
		switch (t2.kind) {
		case '+':
			left = left + term(ts, is);
			t2 = ts.get(is);
			break;
		case '-':
			left = left - term(ts, is);
			t2 = ts.get(is);
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

	catch (Terminate& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}

	catch (...) {
		std::cerr << "Something went wrong...\n";
		return 2;
	}
}