//Write a function, string cat_dot(const string& s1, const string& s2),
//that concatenates two strings with a dot in between.For example, cat_
//dot("Niels", "Bohr") will return a string containing Niels.Bohr.
#include <iostream>
#include <string>

static auto cat_dot(const std::string& s1, const std::string& s2)
{
	return s1 + "." + s2;
}

int main()
{
	std::string s1 = "Niels";
	std::string s2 = "Bohr";

	std::cout << cat_dot(s1, s2) << "\n";
}