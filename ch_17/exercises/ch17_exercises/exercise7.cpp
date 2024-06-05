//7. Write a program that reads characters from cin into an array that you
//allocate on the free store.Read individual characters until an exclamation
//mark(!) is entered.Do not use a std::string.Do not worry about memory
//exhaustion.

#include <iostream>
//hold max size
int main() {
	std::cout << "Please enter some characters. Press ctrl+z or ! to exit...\n";

	auto* p1 = new char[6] {};
	p1[5] = '\0';

	auto i{ 0 };
	auto max_sz{ 5 };

	for (auto c = '?'; std::cin.get(c);)
	{
		if (c == '!')
		{
			std::cout << "Exiting...";
			delete[] p1;
			return 0;
		}

		if (i < max_sz)
		{
			p1[i++] = c;
			continue;
		}

		max_sz *= 2;
		auto* p2 = new char[max_sz + 1] {};

		for (auto internal_i = 0; internal_i < i; ++internal_i)
		{
			p2[internal_i] = p1[internal_i];
		}

		p2[max_sz] = '\0';
		delete[] p1;
		p1 = p2;
		p1[i++] = c;
	}
}