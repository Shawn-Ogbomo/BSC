//Write a program to read a file of whitespace - separated numbers and output them in order(lowest value first), one value per line.Write a value
//only once, and if it occurs more than once write the count of its occurrences on its line.For example, 7 5 5 7 3 117 5 should give
//3
//5 3
//7 2
//117

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

//SORT THE VECTOR OF PAIRS LEXICOGRAPHICALLY BY KEY

//DISPLAY FUNCTION
	//IF VECTOR IS NOT EMPTY
		//LOOP
			//IF OCCURENCES IS 0 OF THE PAIR
				// DONT DISPLAT THE VALUE OF THE PAIR
				// NEXT
			// END IF
			// DISPLAY THE PAIRS KEY AND VALUE
		//END LOOP
	//END IF

#include <iostream>
#include <fstream>
#include <ios>

int main() {
	std::string filename;

	std::cin >> filename;

	std::ifstream ifs{ filename };

	if (!ifs)
	{
		std::cerr << "Sorry the file: " << filename << " does not exist...\n";
		ifs.clear(ifs.exceptions() | std::ios::badbit);
		return 1;
	}
}