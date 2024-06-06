//9. Which way does the stack grow : up(toward higher addresses) or down(toward
//	lower addresses) ? Which way does the free store initially grow(that
//		is, before you use delete) ? Write a program to determine the answers.

//Heap grows towards higher addresses
//Stack grows towards lower addresses
#include <iostream>

int main() {
	const auto max_sz{ 10 };
	auto* p1 = new int[10] {};
	const int vals[]{ 1,2,3,4,5,6,7,8,9,10 };

	for (auto i = 0; i < max_sz; ++i)
	{
		std::cout << "heap [" << i << "] " << &p1[i] << "\n";
		std::cout << "stack[" << i << "] " << &vals[i] << "\n\n";
	}

	delete[] p1;
}