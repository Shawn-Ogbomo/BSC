#include<iostream>
#include "patron.h"
//Patron::Patron()
//	:name{},
//	card_number{},
//	fees{}
//{
//}
Patron::Patron(std::string member_name, std::string member_card_number)
	: name{ member_name },
	card_number{ member_card_number },
	fees{ 0.00 }
{
	if (!is_valid())
	{
		throw std::runtime_error("Invalid member credentials...");
	}
}
std::string Patron::get_name() const
{
	return name;
}
std::string Patron::get_card_number() const
{
	return card_number;
}
double Patron::get_fees() const
{
	if (fees > 0) { std::cout << get_name() << " Owes " << "$" << fees; }
	return fees;
}
bool Patron::is_valid()
{
	if ((name.size() < first_name_max + last_name_max) && (card_number.size() == 14 && (std::count(name.begin(), name.end(), ' ') == 1)))
	{
		for (const auto& target : name)
		{
			if (!isalpha(target) && !isspace(target))
			{
				throw std::runtime_error("invalid name...");
			}
		}

		for (const auto& target : card_number)
		{
			if (!isdigit(target))
			{
				throw std::runtime_error("invalid card number...");
			}
		}
		return true;
	}
	return false;
}