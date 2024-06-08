//Split the binary I / O program from §11.3.2 into two : one program that
//converts an ordinary text file into binary and one program that reads
//binary and converts it to text.Test these programs by comparing a text
//file with what you get by converting it to binary and back

#include <iostream>
#include <fstream>
#include <vector>
#include <span>

int main() {
	std::cout << "Enter a file name: ";

	std::string file_name;

	std::cin >> file_name;

	std::ifstream ifs{ file_name };

	if (!ifs)
	{
		std::cerr << "Sorry the file: " << file_name << " does not exist\n";
		ifs.clear(ifs.exceptions() | std::ios::badbit);
		return 1;
	}

	std::vector<std::string> words;

	for (std::string word; ifs >> word;)
	{
		words.push_back(word);
	}

	//WRITE TO AN OUTPUT FILE IN BINARY
	std::ofstream ofs{ "output.txt", std::ios_base::binary };

	for (const auto& word : words)
	{
		/*ofs.write(std::as_bytes(word), sizeof(int));*/
	}
}