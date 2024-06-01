////Drill 1- 9 ch 17
////prints out values of assumed to have elements
#include <iostream>

static void print_array10(std::ostream& os, const int* a, int sz)
{
	auto val{ sz };

	for (auto i = 0; i < sz; ++i)
	{
		os << a[i] << " ";
	}
}

int main() {
	constexpr auto max_sz{ 21 };
	auto* vals{ new int[max_sz] {} };

	for (auto i = 0, val = 100; i < max_sz; ++i, ++val)
	{
		vals[i] = val;
	}

	print_array10(std::cout, vals, max_sz);

	delete[] vals;
}