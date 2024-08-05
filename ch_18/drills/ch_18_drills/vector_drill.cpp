//Standard library vector drill
#include <vector>
#include <iostream>
#include <algorithm>

static auto print_vec(const std::vector<int>& v) {
	for (auto& val : v)
	{
		std::cout << val << " ";
	}

	std::cout << "\n\n";
}

static auto f(const std::vector<int>& v) {
	auto lv{ std::vector<int>(v.size()) };

	std::copy(v.begin(), v.end(), lv.begin());

	print_vec(lv);

	auto lv2{ std::vector<int>{lv} };

	print_vec(lv2);
}

auto gv{ std::vector<int>{1} };

int main()
{
	for (auto val = 1, count = 1, sz = 10; val *= 2;)
	{
		if (count == sz)
		{
			break;
		}

		gv.push_back(val);
		++count;
	}

	print_vec(gv);

	f(gv);

	auto vv{ std::vector<int>{1,2,6,24,120,720,5040,40320,362880,3628800} };

	f(vv);
}