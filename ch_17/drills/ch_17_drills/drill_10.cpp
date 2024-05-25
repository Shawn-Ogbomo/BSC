//drill 10
#include <iostream>
#include <vector>

static void print_vector(std::ostream& os, const std::vector<int>& vals)
{
	for (auto& val : vals)
	{
		os << val << " ";
	}
}

int main() {
	std::vector<int> vals{ 1,2,3,4,5,6,7,8,9,10 };

	print_vector(std::cout, vals);
}