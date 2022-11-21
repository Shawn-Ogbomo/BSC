#include "library.h"
Patron::Patron(std::string member_name, std::string member_card_number)
	:name{ member_name }, card_number{ member_card_number }, fees{ 0.00 }, in_debt{ false }
{
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

bool debt(const Patron& member)
{
	return member.get_fees() < 0;
}