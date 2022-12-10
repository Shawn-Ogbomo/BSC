/*
	calculator08buggy.cpp

	Helpful comments removed.

	We have inserted 3 bugs that the compiler will catch and 3 that it won't.
*/
#include<iostream>
#include<cmath>
#include<string>
#include<vector>
#include<algorithm>
#include<stdexcept>
struct Token
{
	char kind;
	std::string name;
	double value;
	Token(char ch) :kind(ch), value(0) { }
	Token(char ch, double val) :kind(ch), value(val) { }
	Token(char ch, std::string test) :kind(ch), value(0), name(test) { }
};
class Token_stream
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
const char let = 'L';
const char quit = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';
const char permanent = 'C';
const std::string declkey = "#";
const std::string ex_key = "exit";
const std::string constant = "const";
constexpr int k = 1000;
const char underscore = '_';
Token Token_stream::get()
{
	if (full) {
		full = false; return buffer;
	}
	char ch;
	std::cin >> ch;
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
	case '$':																									//for square root function cannot use s or S.. it will conflict with names starting with s and display an error.
	case'^':																									// for exponent
		return Token(ch);
	case '.':
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
		double val;
		std::cin >> val;
		return Token(number, val);
	}
	default:
	{
		if (isalpha(ch))																																// added  selection to verify names start is an alphabet.
		{
			std::string s;
			s += ch;
			while (std::cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == underscore)) s += ch;
			std::cin.unget();
			if (s == ex_key) return Token(quit);
			else if (s == constant) return Token(permanent);
			return Token(name, s);
		}
		else
		{
			std::string key = "";
			key += ch;
			if (key == declkey) return Token(let);
		}
	}
	std::cerr << "\nBad token: " << ch << "\n";
	throw std::runtime_error("");
	}
}

void Token_stream::ignore(char c)
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
	double get_value(std::string s) const																									//added exception to handle paragraphs
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
	double declaration()																														//assigns the name of the token to the variable...			chamge this...
	{
		char type = 'V';																														//added
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
			if (var_table[i].name == s && !var_table[i].is_constant())									// name is in the vector and the token is not marked as constant...
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
//std::vector<Variable> names;																			// now using symbol stable instead of vector variable names...
//double get_value(std::string s)																		//added exception to handle paragraphs
//{
//	for (unsigned int i = 0; i < names.size(); ++i)
//		if (names[i].name == s) return names[i].value;
//	std::cerr << "get: undefined name " << s << "\n";
//	throw std::runtime_error("");
//}

//void set_value(std::string s, double d)
//{
//	for (unsigned int i = 0; i < names.size(); ++i)
//	{
//		if (names[i].name == s && !names[i].is_constant())												// name is in the vector and the token is not marked as constant...
//		{
//			names[i].value = d;
//			return;
//		}
//	}
//	std::cerr << "set: undefined name, " << s << "\n";
//}

double primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')') std::cerr << "')' expected";
		return d;
	}
	case '-':
		return -primary();
	case '$':
	{
		double d = expression();
		if (d < 0)
		{
			std::cout << "\nCannot find the square root of a negative value...";
		}
		d = std::sqrt(d);
		return d;
	}
	case'^':										// was previously 'p'
	{
		double d = expression();
		double s = primary();
		d = std::pow(d, s);
		return d;
		break;
	}
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
//double declaration()																														//assigns the name of the token to the variable...
//{
//	char type = 'V';
//	Token t = ts.get();
//	if (t.kind == permanent)
//	{
//		type = t.kind;
//		t = ts.get();
//	}
//	if (t.kind != name) std::cerr << "name expected in declaration\n";
//	std::string name = t.name;
//	if (is_declared(name)) std::cerr << name << " declared twice\n";
//	Token t2 = ts.get();
//	if (t2.kind != '=') std::cerr << "= missing in declaration of " << name << "\n";
//	double d = expression();
//	names.push_back(Variable(type, name, d));
//	return d;
//}
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
	while (true) try {
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