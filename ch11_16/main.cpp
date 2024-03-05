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
		//READ FILE
			//LOOP WHILE DATA IN THE FILE
				//CHECK IF THE NUMBER IS IN THE VECTOR
					// IF IT IS NOT
						//CREATE STD::PAIR OF THE NUMBER AND OCCURENCES {0}
						//PUSH TO BACK OF VECTOR
						// CONTINUE
					//END IF
				// INCREMENT THE OCCURENCES OF THE NUMBER
				//NEXT NUMBER
			//END LOOP

		auto found = std::find_if(vals.begin(), vals.end(), [val](std::pair<int, int>lhs) {
			return lhs.first == val; });

		if (found == std::end(vals))
		{
			vals.emplace_back(std::pair{ val, 1 });
			continue;
		}

		found->second++;
	}

	//SORT THE VECTOR OF PAIRS LEXICOGRAPHICALLY BY KEY
	std::sort(vals.begin(), vals.end(), [](std::pair<int, int> lhs, std::pair<int, int> rhs) {
		return lhs.first < rhs.first;
		});

	//DISPLAY
	//IF VECTOR IS NOT EMPTY
		//LOOP
			//IF OCCURENCES IS 0 OF THE PAIR
				// DONT DISPLAT THE VALUE OF THE PAIR
				// CONTINUE
			// END IF
			// DISPLAY THE PAIRS KEY AND VALUE
		//END LOOP
	//END IF

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