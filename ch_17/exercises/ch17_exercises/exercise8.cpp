//8. Do exercise 7 again, but this time read into a std::string rather than to
//memory you put on the free store(string knows how to use the free store
//	for you).
#include <iostream>

int main() {
	std::cout << "Please enter some strings. Press ctrl+z or ! to exit...\n";

	for (std::string s; std::cin >> s;)
	{
		if (s == "!")
		{
			std::cout << "Exiting...";
			return 0;
		}

		std::cout << s << "\n";
	}
}