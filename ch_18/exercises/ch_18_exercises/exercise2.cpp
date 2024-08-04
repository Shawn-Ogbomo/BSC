//2. Write a function, char* findx(const char* s, const char* x), that finds the
//first occurrence of the C - style string x in s.Do not use any standard library functions.Do not use subscripting; use the dereference operator * instead
#include <iostream>

static auto findx(const char* s, const char* x) -> char*
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

int main()
{
	const auto* name = "shawn";
	const auto* text = "sposjfspodjshawnfosdfjsodjf";
	const auto* found = findx(text, name);

	auto index = 0;

	while (found && index < 5)
	{
		std::cout << *found;
		++found;
		++index;
	}
}