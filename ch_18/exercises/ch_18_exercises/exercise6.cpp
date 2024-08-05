//Modify cat_dot() from the previous exercise to take a string to be used as
//the separator(rather than dot) as its third argument.
#include <iostream>
#include <string>

static auto cat_dot(const std::string& s1, const std::string& s2, const std::string& s)
{
	return s1 + s + s2;
}

int main()
{
	std::cout << cat_dot("Shawn", "O", "***") << "\n";
	std::cout << cat_dot("Shawn", "O", "777") << "\n";
}