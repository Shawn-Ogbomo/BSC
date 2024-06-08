//10. Look at your solution of exercise 7. Is there any way that input could
//get the array to overflow; that is, is there any way you could enter more
//characters than you allocated space for (a serious error) ? Does anything
//reasonable happen if you try to enter more characters than you allocated ?

//Yes simply write data to an invalid memory location
//writing data is possible to invalid memory since pointers don't
//store the max number of bytes to prevent out of range errors
//writing to invalid memory corrupts the stack and prevents a successful return
//std::out_of_range is not thrown for pointer types
#include <iostream>

int main() {
	std::cout << "Enter 3 characters, press ! to exit...\n";

	auto i{ 0 };
	const auto* p1 = new char[3];

	for (auto c = '?'; std::cin.get(c);)
	{
		if (c == '!')
		{
			std::cout << "Exiting...\n\n";
			return 0;
		}

		p1[i++];
	}
}