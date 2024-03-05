//Write a program that reads a text file and writes out how many characters
//of each character classification are in the file.

#include <iostream>
#include <string_view>
#include <fstream>
#include <cctype>
#include <ios>
#include <map>

static std::map<std::string, int> character_classifications_map{
{ "isspace", 0 },{ "isalpha",0 },{ "isdigit",0 },{ "isxdigit",0} ,{ "isupper",0 },{ "islower",0 },
{ "isalnum",0 },{ "iscntrl",0 },{ "ispunct",0 }, { "isprint",0 },{ "isgraph",0 }
};

void increment_character_classification(char c) {
	if (isspace(c)) {
		character_classifications_map.find("isspace")->second++;
	}

	if (isalpha(c)) {
		character_classifications_map.find("isalpha")->second++;
	}

	if (isdigit(c)) {
		character_classifications_map.find("isdigit")->second++;
	}

	if (isxdigit(c)) {
		character_classifications_map.find("isxdigit")->second++;
	}

	if (isupper(c)) {
		character_classifications_map.find("isupper")->second++;
	}

	if (islower(c)) {
		character_classifications_map.find("islower")->second++;
	}

	if (isalnum(c)) {
		character_classifications_map.find("isalnum")->second++;
	}

	if (iscntrl(c)) {
		character_classifications_map.find("iscntrl")->second++;
	}

	if (ispunct(c)) {
		character_classifications_map.find("ispunct")->second++;
	}

	if (isprint(c)) {
		character_classifications_map.find("isprint")->second++;
	}

	if (isgraph(c)) {
		character_classifications_map.find("isgraph")->second++;
	}
}

void character_classification_totals() {
	std::cout << "\nCharacter classification totals...\n\n";

	for (const auto& [key, value] : character_classifications_map)
	{
		std::cout << key << " " << value << " " << "\n";
	}
}

int main() {
	std::cout << "This program will read all charaacters in the file and write out how many characters of each character\nclassification are in the file.\n\nEnter a file name: ";

	std::string filename;

	std::cin >> filename;

	std::ifstream ifs{ filename };

	if (!ifs)
	{
		std::cerr << "Sorry the file: " << filename << " does not exist...\n";
		ifs.clear(ifs.exceptions() | std::ios::badbit);
		return 1;
	}

	for (char c{}; ifs.get(c);) {
		increment_character_classification(c);
	}

	character_classification_totals();
}