//Write versions of the cat_dot()s from the previous exercises to take
//C - style strings as arguments and return a free - store - allocated C - style string
//as the result.Do not use standard library functions or types in the implementation.Test these functions with several strings.Be sure to free
//(using delete) all the memory you allocated from free store(using new).
//Compare the effort involved in this exercise with the effort involved for
//exercises 5 and 6.
#include <iostream>

static auto cat_dot(const char* s1, const char* s2, const char* s3 = " ") -> const char*
{
	if (!s1 || !s2)
	{
		return nullptr;
	}

	auto sz_s1 = 0;

	auto* p1 = s1;

	while (*p1 != '\0')
	{
		++sz_s1;
		++p1;
	}

	auto sz_s2 = 0;

	auto* p2 = s2;

	while (*p2 != '\0')
	{
		++sz_s2;
		++p2;
	}

	auto sz_s3 = 0;

	auto* p3 = s3;

	while (*p3 != '\0')
	{
		++sz_s3;
		++p3;
	}

	auto* new_str = new char[sz_s1 + sz_s2 + sz_s3 + 1] {};

	for (auto i = 0; i < sz_s1; ++i)
	{
		new_str[i] = s1[i];
	}

	for (auto internal_i = 0, pos = sz_s1; internal_i < sz_s3; ++internal_i, ++pos)
	{
		new_str[pos] = s3[internal_i];
	}

	for (auto j = 0, pos2 = sz_s1 + sz_s3; j < sz_s2; ++j, ++pos2)
	{
		new_str[pos2] = s2[j];
	}

	return new_str;
}

int main()
{
	auto* s = cat_dot("shawn", "o", "***");
	auto* s2 = cat_dot("shawn", "7777777");
	auto* s3 = cat_dot("shawn1111111", "777777777", "_______");
	auto* s4 = cat_dot("Shawn", "777");

	std::cout << s << "\n\n" << s2
		<< "\n\n" << s3 << "\n\n"
		<< s4 << "\n\n";

	char s5[] = { 's','d' ,'\0' };

	std::cout << s5 << "\n\n";

	char s6[] = { "777" };

	std::cout << s6 << "\n\n";

	delete[] s;
	delete[] s2;
	delete[] s3;
	delete[] s4;
}