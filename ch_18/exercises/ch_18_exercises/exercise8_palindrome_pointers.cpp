//rewrite all the functions in §18.7 to use the approach of making a backward copy of the string and then comparing;
// for example, take "home",
//generate "emoh", and compare those two strings to see that they are
//different, so home isn’t a palindrome.
#include <iostream>

constexpr int max = 128;

static auto is_palindrome(const char* first, const char* last)
{
	char str_cpy[max]{};

	auto sz = std::strlen(first) - 1;

	for (size_t i = 0, j = sz; i <= sz; ++i, --j) {
		str_cpy[i] = first[j];

		if (str_cpy[i] != first[i])
		{
			return false;
		}
	}

	return true;
}

static std::istream& read_word(std::istream& is, char* buffer, int max_sz)
{
	is.width(max_sz);
	is >> buffer;
	return is;
}

int main()
{
	try
	{
		for (char s[max]; read_word(std::cin, s, max); ) {
			std::cout << s << " is";

			if (!is_palindrome(&s[0], &s[strlen(s) - 1])) {
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