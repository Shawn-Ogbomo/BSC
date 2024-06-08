//Write a program that reads a file of whitespace - separated numbers and
//outputs a file of numbers using scientific format and precision 8 in four
//fields of 20 characters per line.

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <ios>

int main() {
	std::cout << "This program will read all the numbers in a file and produce a new file with output formatting.\nEnter a file name: ";

	std::string filename;

	std::cin >> filename;

	std::ifstream ifs{ filename };

	if (!ifs)
	{
		std::cerr << "Sorry the file: " << filename << " does not exist...\n";
		ifs.clear(ifs.exceptions() | std::ios::badbit);
		return 1;
	}

	std::vector<double> nums;

	for (double num = 0; ifs >> num;)
	{
		nums.push_back(num);
	}

	std::ofstream ofs{ "output.txt" };

	std::cout << "\nnumbers written to file in scientific format...\n\n";

	auto count = 0;

	for (const auto& num : nums)
	{
		ofs << std::scientific << "|" << std::setw(20) << num << std::setprecision(8);
		++count;

		if (count % 4 == 0)
		{
			ofs << "|\n";
		}
	}
}