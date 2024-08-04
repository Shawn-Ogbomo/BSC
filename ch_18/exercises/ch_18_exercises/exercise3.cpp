//Write a function, int strcmp(const char* s1, const char* s2), that compares
//C - style strings.Let it return a negative number if s1 is lexicographically
//before s2, zero if s1 equals s2, and a positive number if s1 is lexicographically after s2.
// Do not use any standard library functions.Do not use
//subscripting; use the dereference operator * instead
#include <iostream>

static auto strcmpp(const char* s1, const char* s2) {
	if (!s1 || !s2)
	{
		throw std::invalid_argument{ "null_ptr" };
	}

	auto sz_s1 = 0;
	auto* p = s1;

	while (*p != '\0')
	{
		++sz_s1;
		++p;
	}

	auto sz_s2 = 0;
	auto* p2 = s2;

	while (*p2 != '\0')
	{
		++sz_s2;
		++p2;
	}

	const auto sz_smallest = sz_s1 < sz_s2 ? sz_s1 : sz_s2;

	auto* p3 = s1;
	auto* p4 = s2;

	for (auto i = 0; i <= sz_smallest; i++)
	{
		if (*p3 < *p4)
		{
			return -1;
		}

		if (*p3 > *p4)
		{
			return 1;
		}

		++p3;
		++p4;
	}

	if (sz_s1 == sz_s2)
	{
		return 0;
	}

	return sz_s1 < sz_s2 ? -1 : 1;
}

int main()
{
	try
	{
		std::cout << strcmpp("A", "A") << "\n";
		std::cout << strcmpp("AA", "AA") << "\n";
		std::cout << strcmpp("A", "B") << "\n";
		std::cout << strcmpp("A", "AA") << "\n";
		std::cout << strcmpp("BB", "AA") << "\n";
		std::cout << strcmpp("ANN", "ANNSSS") << "\n";
		std::cout << strcmpp(nullptr, nullptr);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << "\n";
		return 1;
	}
}