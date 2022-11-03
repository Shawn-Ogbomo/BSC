#include <iostream>
#include <string>
#include <vector>
#include <ctime>
enum State {
	rock,
	paper,
	scissors,
};
State WinsAgainst[3] = {
	scissors,
	rock,
	paper,
};
struct Token																																//composes token...
{
	char kind;
	int value;
	std::string name;
	Token(char ch) :kind(ch), name(""), value(0) { }
	Token(char ch, const std::string n, const int val) :kind(ch), name(n), value(val) { }
};
struct Token_stream																															// holds token...
{
	Token get();
};
int randRange(int low, int high);
int set_value(const std::string v);
void game();
void clean_up_mess();
const std::string help = "h";
const char quit = 'q';
const char invalid = '!';
const char name = 'n';
const std::string end = "q";
Token_stream ts;
std::vector<std::string> valid_options = { "rock","paper","scissors" };
int main()
{
	game();
}
int randRange(int low, int high)
{
	return rand() % (high - low + 1) + low;
}
int set_value(const std::string v)
{
	for (unsigned int i = 0; i < valid_options.size(); ++i)
	{
		if (v == valid_options[i])
		{
			return i;
		}
	}
	throw std::runtime_error("\ninvalid input.\nRestarting...\n press ; to continue...\n");
}
void game()
{
	srand(unsigned(time(NULL)));
	while (true) try
	{
		Token player1 = ts.get();
		if (player1.kind == quit) return;
		const int sim = randRange(0, 2);
		if (WinsAgainst[player1.value] == sim) { std::cout << "You win...\n"; }
		else if (WinsAgainst[sim] == player1.value) { std::cout << "You lose...\n"; }
		else { std::cout << "Tie...\n"; }
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << "\n";
		clean_up_mess();
	}
}
void clean_up_mess()
{
	char c;
	while (std::cin >> c && c != ';');
}
Token Token_stream::get()
{
	std::string choice = "";
	std::cin >> choice;
	for (unsigned int i = 0; i < choice.size(); ++i)
	{
		choice[i] = std::tolower(choice[i]);
	}
	if (choice == end)
	{
		std::cout << "exiting....";
		return Token(quit);
	}
	else if (choice == help)
	{
		std::cout << "This program plays rock paper scissors with a simulator.\nEnter the string rock, paper, or scissors in upper or lowercase."
			<< "\nTo quit, press q\nTo display instructions press h";
		throw std::runtime_error("\nrestarting...\npress ; to continue...");
	}
	return Token(name, choice, set_value(choice));
}