//5. Write a function, char* findx(const char* s, const char* x), that finds the
//first occurrence of the C - style string x in s.
#include <iostream>

static char* findx(const char* s, const char* x) {
	if (!s || !x)
	{
		return nullptr;
	}

	auto sz_s{ 0 };

	while (s[sz_s] != '\0')
	{
		++sz_s;
	}

	auto sz_x{ 0 };

	while (x[sz_x] != '\0')
	{
		++sz_x;
	}

	if (sz_x > sz_s || !sz_x || !sz_s) {
		return nullptr;
	}

	for (auto i = 0, j = 0, count = 0, pos_found = 0; i < sz_s; ++i)
	{
		if (s[i] != x[j])
		{
			j = 0;
			count = 0;
			continue;
		}

		pos_found = i;
		++count;
		++j;

		if (count == sz_x)
		{
			auto* found = new char[count + 1] {};
			pos_found -= (count - 1);

			for (auto internal_i = 0; internal_i < count; ++internal_i)
			{
				found[internal_i] = s[pos_found++];
			}

			found[count] = '\0';
			return found;
		}
	}

	return nullptr;
}

int main() {
	char s1[]{ 's','h','a','w','n','\0' };
	char s2[]{ 'i','f','b','z','2' ,'s','h','a','w','n','y','1','2','\0' };

	const auto* p1 = findx(s2, s1);

	std::cout << "address of p1:" << &p1 << "\n";
	std::cout << "Value: " << p1;

	delete[] p1;
}