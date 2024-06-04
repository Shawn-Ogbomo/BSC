//7. Write a program that reads characters from cin into an array that you
//allocate on the free store.Read individual characters until an exclamation
//mark(!) is entered.Do not use a std::string.Do not worry about memory
//exhaustion.

#include <iostream>

int main() {
	std::cout << "Please enter some characters. Press ! to exit...\n";

	for (auto c = '?'; std::cin >> c;)
	{
		if (c == '!')
		{
			std::cout << "Exiting...";
			return 0;
		}

		auto* p1 = new char[1];
		p1[0] = c;
	}
}