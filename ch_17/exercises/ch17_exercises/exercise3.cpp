//EXERCISE 3
//Write a function, void to_lower(char* s), that replaces all uppercase characters
//in the C - style string s with their lowercase equivalents.For example,
//Hello, World! becomes hello, world!.Do not use any standard
//library functions.A C - style string is a zero - terminated array of characters,
//so if you find a char with the value 0 you are at the end.

#include <iostream>

static void to_lowerr(char* s) {
	if (!s)
	{
		std::cerr << "empty...\n";
		return;
	}

	auto index{ 0 };

	while (s[index] != '\0')
	{
		if (const auto dec = static_cast<int>(s[index]); dec >= 65 && dec <= 90)
		{
			s[index] += 32;
		}

		++index;
	}
}

int main() {
	char sentence[]{ 'H','e','L','l','o','!',' ','M','y',' ','N','A','M','e',' ','i','S',' ','S','h','a','W','N','!','\0' };
	char empty_c_string[]{ '\0' };

	to_lowerr(nullptr);
	to_lowerr(sentence);
	to_lowerr(empty_c_string);

	std::cout << sentence;
	std::cout << empty_c_string;
}