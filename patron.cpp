#include<iostream>
#include "patron.h"
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
Patron::Patron(std::string member_name, std::string member_card_number, double debt)
	:name{ member_name },
	card_number{ member_card_number },
	fees{ debt }
{
	if (!is_valid() || debt < 0)
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

bool in_debt(const Patron& member)
{
	if (member.get_fees() > 0) { std::cout << member.get_name() << " Owes " << "$" << member.get_fees() << "\n"; }
	return member.get_fees() > 0;
}