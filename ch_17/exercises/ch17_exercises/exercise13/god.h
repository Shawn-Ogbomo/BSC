#ifndef GOD_H
#define GOD_H

#include <string>
#include <iostream>
#include <string_view>

struct God
{
public:
	God(std::string_view n, std::string_view m, std::string_view w, std::string_view v = "")
		:name{ n },
		mythology{ m },
		weapon{ w },
		vehicle{ v } {};

	void print_all() const
	{
		std::cout << " " << mythology << " \n"
			<< " " << name << " \n"
			<< (!vehicle.empty() ? " " + vehicle + "\n" : "")
			<< " " << weapon;
	}

	std::string name;
	std::string mythology;
	std::string weapon;
	std::string vehicle;
};

#endif // !GOD_H