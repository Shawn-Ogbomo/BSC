#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <string>
class Name_pairs
{
public:
	void read_names();
	void read_ages();
	void print() const;
	void sort();
private:
	std::vector<std::string> names;
	std::vector<double> ages;
};
const std::string quit = "q";
int main()
{
	Name_pairs people;
	people.read_names();
	people.read_ages();
	people.sort();
	people.print();
}
double search(const std::vector<std::string>& original, const std::string target, const std::vector<double>& vals)
{
	for (unsigned int i = 0; i < original.size(); ++i)
	{
		if (target == original[i])
		{
			return vals[i];
		}
	}
}
void Name_pairs::read_names()
{
	while (true)try
	{
		std::cout << "Enter a set of names...\nPress 'q' to stop: ";
		for (std::string name; std::cin >> name;)
		{
			if (name == quit) { return; }
			for (const auto& target : name)
			{
				if ((target < 65 || target >90) && (target < 97 || target > 122))																			//validates name
				{
					throw std::runtime_error("Invalid name...\n enter your name again...");
				}
			}
			names.push_back(name);
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << "\n";
	}
}
void Name_pairs::read_ages()
{
	if (names.size())
	{
		while (true)try
		{
			std::cout << "Enter the age(s) please: ";
			for (double age{}; std::cin >> age && ages.size() < names.size();)
			{
				ages.push_back(age);
				if (ages.size() == names.size()) { return; }
			}
			if (!std::cin) { throw std::runtime_error("Either your number is too large, too small, or it is a character...\nTry entering an age again..."); }
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << "\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
}
void Name_pairs::print() const
{
	if (names.size())
	{
		for (unsigned int i{}; i < names.size(); ++i)
		{
			std::cout << names[i] << " " << ages[i] << "\n";
		}
	}
	std::cout << "exiting...";
}
void Name_pairs::sort()
{
	std::vector<std::string> names_cpy = names;
	std::vector<double> ages_new;
	std::sort(names.begin(), names.end());
	for (const auto& target : names)
	{
		ages_new.push_back(search(names_cpy, target, ages));
	}
	ages = ages_new;
}