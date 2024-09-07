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
#include <cmath>
#include <cctype>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string_view>

#include "util.h"
#include "roman.h"
#include "exceptions.h"

struct Token {
public:
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
	auto get(std::istream& is = std::cin) -> Token;

	auto unget(const Token& t) -> void
	{
		if (full) {
			throw  std::invalid_argument{ "cannot put token into full stream..." };
		}

		buffer = t;
		full = true;
	}

	auto ignore(char c) -> void;
private:
	bool full{};
	Token buffer;
};

const auto print = ';';
const auto  quit = 'q';
const auto  help = 'h';
const auto let = '#';
const auto name = '~';
const auto assignment = '=';
const auto underscore = '_';
const auto permanent = 'k';
const auto roman_numeral = 'r';
const auto file = 'x';
const auto output_to_file = 'y';

std::string_view constant = "const";
std::string_view ex_key = "exit";

//CHECKS FOR NAME,CONST,EXIT, AND ROMAN INT
static auto remaining_case(char c, std::istream& is) -> Token
{
	if (c == name)
	{
		std::string s;

		while (is.get(c) && c == underscore || isalpha(c) || isdigit(c))
		{
			s += c;
		}

		is.unget();

		if (s.empty() || s.front() == underscore || isdigit(s.front()))
		{
			throw Invalid_format{ "Invalid name format..." };
		}

		Util::format_string(s);

		return Token(s);
	}

	if (c == 'c' || c == 'e')
	{
		std::string pattern = "abcdefghijklmnopqrstuvwxyz";
		std::string internal_s;

		is.unget();

		while (is.get(c) && (pattern.find(c) != std::string::npos))
		{
			internal_s += c;
		}

		if (internal_s == constant)
		{
			return Token{ permanent };
		}

		if (internal_s == ex_key)
		{
			return Token{ quit };
		}

		throw Invalid_format{ "your input is not const or exit..." };
	}

	is.putback(c);

	Roman_int rmn;
	is >> rmn;

	Util::check_stream(is, "couldn't build a roman int...");

	return Token{ rmn };
}

auto Token_stream::get(std::istream& is) -> Token
{
	if (full)
	{
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
		throw  Invalid_format{ "Roman numerals only." };
	}

	default:
		if (isspace(c))
		{
			return Token(print);
		}

		if (isalpha(c) && is.peek() == '\n')
		{
			if (c == quit) {
				return Token(quit);
			}

			if (c == help)
			{
				return Token{ help };
			}

			if (c == file)
			{
				return Token{ file };
			}

			if (c == output_to_file)
			{
				return Token{ output_to_file };
			}
		}

		return remaining_case(c, is);
	}
}

Roman_int statement(Token_stream& ts, std::istream& is = std::cin, std::ostream& os = std::cout);
Roman_int expression(Token_stream& ts, std::istream& is = std::cin);

// ignores print characters ';'
auto Token_stream::ignore(char c) -> void
{
	if (full && c == buffer.kind)
	{
		full = false;
		return;
	}

	std::cout << "Press; to continue...\n";
	full = false;
	char ch;

	while (std::cin >> ch)
	{
		if (ch == c)
		{
			return;
		}
	}
}

static auto  clean_up_mess(Token_stream& ts) -> void
{
	ts.ignore(print);
}

const auto prompt = '>';
const auto result = '=';

class Variable {
public:
	Variable() = default;
	explicit  Variable(const std::string& name, const Roman_int& val, bool qualifier = false)
		:n{ name },
		v{ val },
		state{ qualifier } {}
	auto value()const -> const Roman_int& { return v; }
	auto name() const -> std::string_view { return n; }
	auto is_const() const -> bool { return state; }
	auto set_value(const Roman_int& val) -> void {
		v = val;
	}
private:
	std::string n;
	Roman_int v;
	bool state{};
};

static auto file_prompt(std::string& f_name) -> void
{
	std::cout << "Enter the name of the file: ";
	std::cin >> f_name;
}

//TAKES INPUT FROM FILE
static auto from_file(Token_stream& ts, std::ostream& os = std::cout) -> void
{
	std::string file_name;
	file_prompt(file_name);
	std::ifstream ifs{ file_name };

	Util::check_stream(ifs, "Oops, the file: " + file_name + " does not exist...", "\nyou pressed ctrl+z\nexiting....");

	while (ifs)try
	{
		os << prompt << " ";

		auto t = ts.get(ifs);

		while (t.kind == print)
		{
			if (ifs.peek() == -1)
			{
				return;
			}

			t = ts.get(ifs);
		}

		ts.unget(t);
		os << result << " " << statement(ts, ifs) << std::endl;
	}
	catch (std::invalid_argument& e)
	{
		os << e.what() << "\n";
		Util::skip_input(ifs, print);
	}

	catch (Invalid_format& internal_e)
	{
		os << internal_e.what() << "\n";
		Util::skip_input(ifs, print);
	}
}

static auto calculate(Token_stream& ts, std::ostream& os = std::cout) -> void;

//SEND OUTPUT TO FILE
static auto to_file(Token_stream& ts, std::ostream& os) -> void
{
	std::cout << "press q or type exit to stop sending output to file...\n";

	calculate(ts, os);
}

static auto help_message(std::ostream& os) -> void
{
	os << "\nCalculator application...\n\n"
		<< "This calculator contains the functions of a basic calculator. \nModulo, exponent, and square root functions are also included.\n"
		<< "The calculator is also capable of creating variables and constants.\n"
		<< "\nFunctions...\n" << "$ = sqrt\nenter-key = print instead of '='\nq-key to quit or type exit to quit\n\n# variable declaration format\n#~shawn=roman_numeral or one space after or before = key\n\n"
		<< "const declaration format \nconst ~shawn=roman_numeral or const ~shawn =roman_numeral or const ~shawn = roman_numeral\n"
		<< "h key to display instructions...\n"
		<< "y key to send all cerr output and standard output to a file\n\n";
}

static auto calculate(Token_stream& ts, std::ostream& os) -> void
{
	while (true)try
	{
		std::cout << prompt << " ";
		auto t = ts.get(std::cin);

		while (t.kind == print)
		{
			t = ts.get(std::cin);
		}

		if (t.kind == quit)
		{
			return;
		}

		if (t.kind == file)
		{
			from_file(ts, os);
			std::cout << "Finished reading file contents.\n";
			continue;
		}

		if (t.kind == output_to_file)
		{
			std::string file_name;	file_prompt(file_name);
			std::ofstream oft{ file_name };

			to_file(ts, oft);
			std::cout << "Finished writing file contents.\n";
			continue;
		}

		if (t.kind == help)
		{
			help_message(os);
			continue;
		}

		ts.unget(t);

		os << result << " " << statement(ts) << std::endl;
	}

	catch (std::invalid_argument& e)
	{
		os << e.what() << "\n";
		clean_up_mess(ts);
	}
}

class Symbol_table {
public:
	static auto declare(Token_stream& ts, const Token& t, std::istream& is = std::cin) -> Roman_int
	{
		auto t2 = ts.get(is);

		if (t2.kind != name)
		{
			throw  Invalid_format{ "invalid token: " + std::string{t2.kind} + " expected a name" };
		}

		if (auto t3 = ts.get(is); t3.kind != print)
		{
			ts.unget(t3);
		}

		if (auto t4 = ts.get(is); t4.kind != assignment)
		{
			throw  Invalid_format{ "invalid token: " + std::string{t4.kind} + " expected " + assignment };
		}

		if (auto t5 = ts.get(is); t5.kind != print)
		{
			ts.unget(t5);
		}

		if (Symbol_table::is_declared(t2.name))
		{
			throw  std::invalid_argument{ t2.name + std::string{" is already declared\n"} };
		}

		auto rmn_numeral = expression(ts, is);
		auto v = (t.kind == let ? Variable{ t2.name, rmn_numeral } : Variable{ t2.name, rmn_numeral, true });

		var_table.push_back(v);
		return v.value();
	}

	static auto is_declared(std::string_view variable_name) -> bool
	{
		return std::any_of(var_table.begin(), var_table.end(), [&variable_name](Variable const& v) {return v.name() == variable_name; });
	}

	static auto value(std::string_view variable_name) -> Roman_int
	{
		if (auto found = std::find_if(var_table.begin(), var_table.end(), [&variable_name](Variable const& v) { return v.name() == variable_name; });
			found != std::end(var_table))
		{
			return found->value();
		}

		throw  std::invalid_argument{ "The variable: " + static_cast<std::string>(variable_name) + " does not exist..." };
	}

	static auto update_value(std::string_view variable_name, const Roman_int& new_value, std::ostream& os = std::cout) -> void
	{
		if (auto found = std::find_if(var_table.begin(), var_table.end(), [&variable_name](Variable const& v) { return v.name() == variable_name; });
			found != std::end(var_table))
		{
			if (found->is_const())
			{
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

auto statement(Token_stream& ts, std::istream& is, std::ostream& os) -> Roman_int
{
	auto t = ts.get(is);

	if (t.kind == let || t.kind == permanent)
	{
		return Symbol_table::declare(ts, t, is);
	}

	if (t.kind == name)
	{
		if (Symbol_table::is_declared(t.name))
		{
			auto t2 = ts.get(is);

			if (t2.kind == print)
			{
				return Symbol_table::value(t.name);
			}

			if (t2.kind == assignment)
			{
				Symbol_table::update_value(t.name, expression(ts, is), os);
				return Symbol_table::value(t.name);
			}
		}

		throw Invalid_format{ "The variable: " + t.name + " does not exist...\n" };
	}

	ts.unget(t);

	return expression(ts, is);
}

static auto primary(Token_stream& ts, std::istream& is = std::cin) -> Roman_int
{
	auto t = ts.get(is);

	switch (t.kind) {
	case '(':
	{
		auto left = expression(ts, is);
		t = ts.get(is);

		if (t.kind != ')')
		{
			throw  Invalid_format{ "')' expected\n" };
		}

		while (is.peek() == '(')
		{
			t = ts.get(is);
			left = left * expression(ts, is);
			t = ts.get(is);

			if (t.kind != ')')
			{
				throw  Invalid_format{ "')' expected\n" };
			}
		}
		return left;
	}

	case roman_numeral:
		return t.v_rmn;
	case name:
		return Symbol_table::value(t.name);
	default:
		throw  Invalid_format{ "\nExpected term..." };
	}
}

static auto term(Token_stream& ts, std::istream& is = std::cin) -> Roman_int
{
	auto left = primary(ts, is);
	auto t2 = ts.get(is);

	while (true)
	{
		switch (t2.kind) {
		case '$':
		{
			left = Roman_int{ integer_to_roman_code(static_cast<int>(std::sqrt(left.as_int()))) };
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

static auto expression(Token_stream& ts, std::istream& is) -> Roman_int {
	auto left = term(ts, is);
	auto t2 = ts.get(is);

	while (true)
	{
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
	try
	{
		Token_stream ts{ std::cin };
		calculate(ts);
	}

	catch (Terminate& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	catch (...)
	{
		std::cerr << "Something went wrong...\n";
		return 2;
	}
}