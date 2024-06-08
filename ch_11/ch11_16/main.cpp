//Write a program to read a file of whitespace - separated numbers and output them in order(lowest value first), one value per line.Write a value
//only once, and if it occurs more than once write the count of its occurrences on its line.For example, 7 5 5 7 3 117 5 should give
//3
//5 3
//7 2
//117

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <ios>

int main() {
	std::cout << "This program reads a file of whitespace - separated numbers and outputs them in order(lowest value first), one  value per line." << "\nWrite a value only once, and if it occurs more than once write the count of its occurrences on its line." << "\nFor example, 7 5 5 7 3 117 5 should give: \n" << "3\n"
		<< "5  3\n" << "7 2" << "\n117 \n"
		<< "\n\nEnter a file name: ";

	std::string filename;

	std::cin >> filename;

	std::ifstream ifs{ filename };

	if (!ifs)
	{
		std::cerr << "Sorry the file: " << filename << " does not exist...\n";
		ifs.clear(ifs.exceptions() | std::ios::badbit);
		return 1;
	}

	std::vector<std::pair<int, int>> vals;

	for (int val{}; ifs >> val;) {
		auto found = std::find_if(vals.begin(), vals.end(), [val](std::pair<int, int>lhs) {
			return lhs.first == val; });

		if (found == std::end(vals))
		{
			vals.emplace_back(std::pair{ val, 1 });
			continue;
		}

		found->second++;
	}

	std::sort(vals.begin(), vals.end(), [](std::pair<int, int> lhs, std::pair<int, int> rhs) {
		return lhs.first < rhs.first;
		});

	if (!vals.empty())
	{
		std::cout << "\n\nresults\n\n";

		for (const auto& [value, occurences] : vals) {
			if (occurences > 1)
			{
				std::cout << value << " " << occurences << "\n";
				continue;
			}

			std::cout << value << "\n";
		}
	}
}