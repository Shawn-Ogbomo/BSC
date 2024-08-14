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

constexpr int limit = 128;

static auto is_palindrome(const char s[], int n) -> bool
{
	int first = 0; // index of first letter
	int last = n - 1; // index of last letter
	while (first < last) { // we haven’t reached the middle
		if (s[first] != s[last]) return false;
		++first; // move forward
		--last; // move backward
	}
	return true;
}

static auto read_word(std::istream& is, char* buffer, int max) -> std::istream&
// read at most max–1 characters from is into buffer
{
	is.width(max); // read at most max–1 characters in the next >>
	is >> buffer; // read whitespace-terminated word,
	// add zero after the last character read into buffer
	return is;
}

static auto check_stream(std::istream& is = std::cin) -> void
{
	if (is.eof() || is.bad())
	{
		throw Terminate{ "exiting..." };
	}

	if (is.fail())
	{
		is.clear();

		for (auto c = '?'; std::cin >> c; )
		{
			if (isdigit(c))
			{
				is.unget();
				throw std::runtime_error{ "" };
			}
		}

		throw Terminate{ "exiting..." };
	}
}

int main()
{
	while (true) try {
		char* s{};

		auto sz = 0;

		std::cin >> sz;

		check_stream();

		if (sz > limit)
		{
			std::cerr << "Invalid sz\n";
			sz = limit;
		}

		s = new char[sz] {};

		if (read_word(std::cin, s, sz)) {
			std::cout << s << " is";

			if (!is_palindrome(s, strlen(s)))
			{
				std::cout << " not";
			}

			std::cout << " a palindrome\n";
		}

		check_stream();

		delete[] s;
	}

	catch (Terminate& e)
	{
		std::cerr << e.what() << "\n";
		return 1;
	}

	catch (std::bad_alloc& e)
	{
		std::cerr << e.what() << "\n";
		return 2;
	}
	catch (std::invalid_argument& e)
	{
		std::cerr << e.what() << "\n";
		return 3;
	}

	catch (std::runtime_error& e)
	{
		std::cerr << e.what() << "\n";
	}
}