//Simple calculator
//revision history
// works on integer values  only
// replaced cin with get in token stream to read whitespace
// changed terminate command from exit to q
//This program implements a basic expression calculator.
//Input from cin; output to cout.
//The grammar for input is :
//Calculation
//statement :
//Print
//Quit
//Calculation Statement
//
//
//
//Statement:
//Declaration
//Expression
//
//Print :
//;
//'\n'
//
//Quit:
//q
//
//Declaration :
//"let" Name "=" Expression
//
//
//Expression :
//Term
//Expression + Term
//Expression - Term
//
//
//
//Term:
//Primary
//Term $(sqrt)
//Term ^ primary
//Term * Primary
//Term / Primary
//Term % Primary
//name
//
//
//Primary :
//(Expression)
//-Primary
//+ Primary
//number
//name
//
//
//Number :
//floating - point - literal
//
//Name :
//	string
//	input comes from cin through token stream

#include<iostream>
#include<cmath>
#include<string>
#include<vector>
#include<algorithm>
#include<stdexcept>
struct Token																												// Represents an element of an expression
{
	char kind;
	std::string name;
	int value;
	Token(char ch) :kind(ch), value(0) { }
	Token(char ch, double val) :kind(ch), value(val) { }
	Token(char ch, std::string n) :kind(ch), value(0), name(n) { }
};
class Token_stream																											// Holds a token
{
	bool full;
	Token buffer;
public:
	Token_stream() :full(0), buffer(0) {}
	Token get();
	void unget(Token t) {
		buffer = t; full = true;
	}
	void ignore(char);
};
constexpr int k = 1000;
const char let = 'L';
const char quit = 'q';
const char print = ';';
const char number = '8';
const char name = 'a';
const char help = 'h';
const char declkey = '#';
const char permanent = 'C';
const char underscore = '_';
const std::string ex_key = "exit";
const std::string constant = "const";
Token Token_stream::get()
{
	if (full) {
		full = false; return buffer;
	}
	char ch;
	std::cin.get(ch);
	switch (ch) {
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case ';':
	case '=':
	case '$':
	case'^':
		return Token(ch);
		//case '.':
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
	{
		std::cin.unget();
		long double val;
		std::cin >> val;
		if (val > INT_MAX)
		{
			std::cout << "Your value is too large try again...\n";
		}
		else if (val < INT_MIN)
		{
			std::cout << "Your value is too small...\n";
		}
		return Token(number, val);
	}
	default:
	{
		if ((isalpha(ch)) && (std::cin.peek() != '\n'))
		{
			std::string s;
			s += ch;
			while (std::cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == underscore)) s += ch;
			std::cin.unget();
			if (s == constant) return Token(permanent);
			return Token(name, s);
		}
		else
		{
			char key = '?';
			key = ch;
			if (key == quit) return Token(quit);
			if (key == declkey) return Token(let);
			if (std::isspace(ch)) return Token(print);
			if (key == help)
			{
				// display instructions for calculator use...
				std::cout << "Calculator application...\n\n"
					<< "This calculator contains the functions of a basic calculator. \nModulo, exponent, and square root functions are also included...\n"
					<< "The calculator is also capable of creating variables and constants; calculations are possible on such expressions.\n"
					<< "Functions... \n\n" << "$ = sqrt\nenter-key = print instead of '='\nq-key to quit or type exit to quit\n#to declare a variable and #const to declare a constant\nh key to display instructions...\n";
				throw std::runtime_error("Press ';' key to continue... ");
			}
			if ((key >= 65 && key <= 90) || (key >= 97 && key <= 122))																			//returns name token if the character is a-z or A-z
			{
				std::string n;
				n += key;
				return Token(name, n);
			}
		}
	}
	std::cerr << "\nBad token: " << ch << "\n";
	throw std::runtime_error("Invalid input...\nPress ; to continue");
	}
}

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
Token_stream ts;
struct Variable
{
	char type;
	std::string name;
	double value;
	Variable(std::string n, double v) : name(n), value(v), type(0) {}
	Variable(char kind, std::string n, double v) : type(kind), name(n), value(v) {}
	bool is_constant() const;
};
double expression();
class Symbol_table
{
public:
	double get_value(std::string s) const
	{
		for (unsigned int i = 0; i < var_table.size(); ++i)
			if (var_table[i].name == s) return var_table[i].value;
		std::cerr << "get: undefined name " << s << "\n";
		throw std::runtime_error("");
	}
	bool is_declared(std::string s) const
	{
		for (unsigned int i = 0; i < var_table.size(); ++i)
			if (var_table[i].name == s) return true;
		return false;
	}
	double declaration()
	{
		char type = 'V';
		Token t = ts.get();
		if (t.kind == permanent)
		{
			type = t.kind;
			t = ts.get();
		}
		if (t.kind != name) std::cerr << "name expected in declaration\n";
		std::string name = t.name;
		if (is_declared(name)) std::cerr << name << " declared twice\n";
		Token t2 = ts.get();
		if (t2.kind != '=') std::cerr << "= missing in declaration of " << name << "\n";
		double d = expression();
		var_table.push_back(Variable(type, name, d));
		return d;
	}
	void set_value(std::string s, double d)
	{
		for (unsigned int i = 0; i < var_table.size(); ++i)
		{
			if (var_table[i].name == s && !var_table[i].is_constant())
			{
				var_table[i].value = d;
				return;
			}
		}
		std::cerr << "set: undefined name, " << s << "\n";
	}
private:
	std::vector<Variable> var_table;
};
Symbol_table st;

double primary()
{
	Token t = ts.get();
	switch (t.kind)
	{
	case '(':
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')') std::cerr << "')' expected";
		return d;
	}
	case '-':
		return -primary();
	case'+':
		return +primary();
	case number:
		return t.value;
	case name:
	{
		ts.unget(t);
		return st.get_value(t.name);
	}
	default:
		std::cerr << "primary expected\n";
	}
}
double term()
{
	double left = primary();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '$':
		{
			if (left < 0)
			{
				std::cout << "\nCannot find the square root of a negative value...\n";
			}
			left = std::sqrt(left);
			continue;
		}
		case'^':
		{
			double right = primary();
			left = std::pow(left, right);
			return left;
			break;
		}
		case '*':
			left *= primary();
			break;
		case '/':
		{	double d = primary();
		if (d == 0) std::cerr << "divide by zero";
		left /= d;
		break;
		}
		case'%':
		{
			double d = primary();
			if (d == 0) std::cerr << "mod by zero";
			left = std::fmod(left, d);
			break;
		}
		case name:
		{
			std::string temp_name = t.name;
			t = ts.get();
			if (t.kind == '=')
			{
				double result = expression();
				st.set_value(temp_name, result);
				return result;
			}
		}
		default:
			ts.unget(t);
			return left;
		}
	}
}
double expression()
{
	double left = term();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '+':
			left += term();
			break;
		case '-':
			left -= term();
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}

double statement()
{
	Token t = ts.get();
	switch (t.kind) {
	case let:
		return st.declaration();
	default:
		ts.unget(t);
		return expression();
	}
}
void clean_up_mess()
{
	ts.ignore(print);
}
const std::string prompt = "> ";
const std::string result = "= ";
void calculate()
{
	while (true) try
	{
		std::cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t = ts.get();
		if (t.kind == quit) return;
		ts.unget(t);
		std::cout << result << statement() << std::endl;
	}
	catch (std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		clean_up_mess();
	}
}
int main()
{
	try {
		calculate();
		return 0;
	}
	catch (std::exception& e) {
		std::cerr << "exception: " << e.what() << std::endl;
		char c;
		while (std::cin >> c && c != ';');
		return 1;
	}
	catch (...) {
		std::cerr << "exception\n";
		char c;
		while (std::cin >> c && c != ';');
		return 2;
	}
}
bool Variable::is_constant() const
{
	if (type != permanent)
	{
		return false;
	}
	else
	{
		std::cout << "\nVariable is defined as a constant. Such variable is unmodifiable\n";
		return true;
	}
}