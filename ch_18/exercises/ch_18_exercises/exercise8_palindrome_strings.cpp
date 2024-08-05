//rewrite all the functions in §18.7 to use the approach of making a backward copy of the string and then comparing; for example, take "home",
//generate "emoh", and compare those two strings to see that they are
//different, so home isn’t a palindrome
#include <ios>
#include <string>
#include <iostream>
#include <algorithm>
#include <string_view>

static auto is_palindrome(const std::string_view& s)
{
	auto s_cpy = static_cast<std::string>(s);

	std::reverse(s_cpy.begin(), s_cpy.end());

	return s_cpy == s;
}

int main()
{
	std::cout << "This program determines if a string is palindrome. \nEnter a string followed by enter\n"
		<< "Press ctrl+z to exit...\n\n";

	for (std::string s; std::cin >> s;)
	{
		std::cout << "\nIs " << s << " Palindrome?\n"
			<< std::boolalpha << is_palindrome(s) << "\n\n";
	}

	std::cout << "Exiting...";
}