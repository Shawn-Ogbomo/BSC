//4. Write a function, char* strdup(const char*), that copies a C - style string
//into memory it allocates on the free store.Do not use any standard library
//functions.
#include <iostream>

static char* strdupp(const char* target) {
	if (!target) {
		return nullptr;
	}

	auto sz{ 0 };

	while (target[sz] != '\0')
	{
		++sz;
	}

	auto target_cpy{ new char[sz + 1] {} };

	target_cpy[sz] = '\0';

	for (auto i = 0; i < sz; ++i)
	{
		target_cpy[i] = target[i];
	}

	return target_cpy;
}

int main() {
	char name[]{ 'S','h','a','w','n','\0' };
	const char* name_cpy = strdupp(name);

	strdupp(nullptr);

	const char* cp{};

	std::cout << "Copy: " << name_cpy << "  Original: " << name;

	delete[] name_cpy;
}