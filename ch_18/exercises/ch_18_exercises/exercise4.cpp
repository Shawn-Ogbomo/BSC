//Consider what happens if you give strdup(), findx(), and strcmp() an argument that is not a C - style string.
// Try it! First figure out how to get a char*
//that doesn’t point to a zero - terminated array of characters and then use
//it(never do this in real — non - experimental — code; it can create havoc).
//Try it with free - store - allocated and stack - allocated “fake C - style strings.”
//If the results still look reasonable, turn off debug mode.Redesign and
//re - implement those three functions so that they take another argument
//giving the maximum number of elements allowed in argument strings.
//Then, test that with correct C - style strings and “bad” strings.
#include <vector>
#include <iostream>
#include <exception>

static auto strdupp(const char* target, int max) -> char* {
	if (!target) {
		return nullptr;
	}

	auto* p = target;

	auto target_sz = 0;

	while (*p != '\0') {
		++p;
		++target_sz;
	}

	if (target_sz > max)
	{
		throw std::invalid_argument{ "Max exceeded..." };
	}

	auto* str_cpy = new char[target_sz + 1] {};

	auto* p2 = str_cpy;

	auto index = 0;

	while (index < target_sz)
	{
		*p2 = (*target);
		++p2;
		++target;
		++index;
	}

	return str_cpy;
}

static auto findx(const char* s, const char* x, int max) -> char*
{
	if (!s || !x)
	{
		return nullptr;
	}

	auto* p = x;

	auto sz_x = 0;

	while (*p != '\0')
	{
		++p;
		++sz_x;
	}

	auto sz_s = 0;

	auto* p2 = s;

	while (*p2 != '\0')
	{
		++p2;
		++sz_s;
	}

	if (sz_x > max || sz_s > max)
	{
		throw std::invalid_argument{ "Max exceeded..." };
	}

	if (sz_x > sz_s)
	{
		return nullptr;
	}

	auto* p3 = const_cast<char*>(s);
	auto* p4 = x;

	for (auto index = 0, count = 0; index < sz_s; ++index)
	{
		if (*p3 != *p4)
		{
			count = 0;
			p4 = x;
			++p3;
			continue;
		}

		++p3;
		++p4;
		++count;

		if (count == sz_x)
		{
			auto pos = index - count;

			while (pos > count)
			{
				--pos;
				--p3;
			}

			return p3;
		}
	}

	return nullptr;
}

static auto strcmpp(const char* s1, const char* s2, int max) -> int {
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

	if (sz_s1 > max || sz_s2 > max)
	{
		throw std::invalid_argument{ "Max exceeded..." };
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
		char vals[] = { '2','7','4' };
		char vals2[] = { '2','7','4' };

		if (const auto* p1 = strdupp(vals, 20)) {
			std::cout << p1 << "\n";
		}

		if (const auto* p2 = strdupp(nullptr, 4)) {
			std::cout << p2;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << "\n";
		return 1;
	}
}