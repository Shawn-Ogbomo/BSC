//Array drill ch18
#include <iostream>

int ga[]{ 1,2,4,8,16,32,64,128,256,512 };

auto f(const int arr[], int sz) {
	int la[10]{};

	for (auto i = 0; i < sz; ++i)
	{
		la[i] = arr[i];
	}

	std::cout << "Stack-array\n";

	for (auto internal_i = 0; internal_i < sz; ++internal_i)
	{
		std::cout << la[internal_i] << "\n\n";
	}

	auto* p{ new int[sz] };

	for (auto j = 0; j < sz; ++j)
	{
		p[j] = arr[j];
	}

	std::cout << "Free-store-array\n\n";

	for (auto internal_j = 0; internal_j < sz; ++internal_j)
	{
		std::cout << p[internal_j] << "\n\n";
	}

	delete[] p;
}

static auto factorial(int val) {
	if (!val)
	{
		return 1;
	}

	auto fact = 1;

	fact *= factorial(val - 1) * val;

	return fact;
}

int main()
{
	f(ga, 10);

	int aa[10]{ };

	for (auto i = 0; i < 10; ++i)
	{
		aa[i] = factorial(i + 1);
	}

	f(aa, 10);
}