//“1. Write a function, char* strdupp(const char*),
//that copies a C-style string into memory it allocates on the free store.
//Do not use any standard library functions.
//Do not use subscripting; use the dereference operator * instead.”
#include <iostream>

static auto strdupp(const char* target) -> char* {
	if (!target) {
		return nullptr;
	}

	auto* p = target;

	auto target_sz = 0;

	while (*p != '\0') {
		++p;
		++target_sz;
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

int main() {
	char name[]{ "shawn" };

	if (auto* p = strdupp(name))
	{
		const auto* p2 = p;

		while (*p2 != '\0') {
			std::cout << *p2;
			++p2;
		}

		delete[] p;
	}
}