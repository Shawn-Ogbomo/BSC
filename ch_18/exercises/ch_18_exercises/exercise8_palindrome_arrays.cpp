//rewrite all the functions in §18.7 to use the approach of making a backward copy of the string and then comparing;
// for example, take "home",
//generate "emoh", and compare those two strings to see that they are
//different, so home isn’t a palindrome.
#include <iostream>

constexpr int max = 128;

static auto  is_palindrome(const char s[], int n)
// s points to the first character of an array of n characters
{
	if (n <= -1)
	{
		throw std::out_of_range{ "negative length" };
	}

	char str_cpy[max]{};

	for (auto i = n - 1, pos = 0; i >= 0; --i, ++pos)
	{
		str_cpy[pos] = s[i];
	}

	for (auto i = 0; i < n; ++i)
	{
		if (str_cpy[i] != s[i])
		{
			return false;
		}
	}

	return true;
}

static std::istream& read_word(std::istream& is, char* buffer, int max_sz)
// read at most max–1 characters from is into buffer
{
	is.width(max_sz); // read at most max–1 characters in the next >>
	is >> buffer; // read whitespace-terminated word,
	// add zero after the last character read into buffer
	return is;
}

int main()
{
	try
	{
		for (char s[max]{}; read_word(std::cin, s, max); ) {
			std::cout << s << " is";

			if (!is_palindrome(s, std::strlen(s)))
			{
				std::cout << " not";
			}

			std::cout << " a palindrome\n";
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << "\n";
		return 1;
	}
}