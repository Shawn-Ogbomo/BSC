//Look at the “array solution” to the palindrome problem in §18.7.2.Fix it
//to deal with long strings by(a) reporting if an input string was too long
//and (b)allowing an arbitrarily long string.Comment on the complexity
//of the two versions
//Current version is paramount in complexity since string size is taken into account;
//permitting an arbitrary long strings comprise allocating heap memory using new and delete to return it to the
//free store
#include <iostream>

class Terminate : public std::exception
{
	using std::exception::exception;
};

static auto is_palindrome(const char s[], std::size_t n) -> bool
{
	std::size_t first = 0; // index of first letter
	std::size_t last = n - 1; // index of last letter
	while (first < last) { // we haven’t reached the middle
		if (s[first] != s[last]) return false;
		++first; // move forward
		--last; // move backward
	}
	return true;
}

static auto read_word(std::istream& is, char* buffer, std::streamsize max) -> std::istream&
// read at most max–1 characters from is into buffer
{
	is.width(max); // read at most max–1 characters in the next >>
	is >> buffer; // read whitespace-terminated word,
	// add zero after the last character read into buffer
	return is;
}

static auto check_stream(const std::istream& is = std::cin) -> void
{
	if (is.eof() || is.fail())
	{
		throw Terminate{ "oops something went wrong. Exiting..." };
	}
}

int main()
{
	try
	{
		for (std::size_t sz = 0, limit = 128; std::cin >> sz;)
		{
			if (sz > limit)
			{
				sz = limit;
			}

			if (auto* s = new char[sz])
			{
				read_word(std::cin, s, sz);

				check_stream();

				std::cout << s << " is";

				if (!is_palindrome(s, strlen(s)))
				{
					std::cout << " not";
				}

				std::cout << " a palindrome\n";

				delete[] s;
			}
		}

		check_stream();
	}

	catch (Terminate& e)
	{
		std::cerr << e.what() << "\n";
		return 1;
	}

	catch (std::exception& e)
	{
		std::cerr << e.what() << "\n";
		return 2;
	}
}