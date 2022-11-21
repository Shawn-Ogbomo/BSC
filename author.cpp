#pragma once
#include "book.h"
Author::Author(std::string first, std::string last)
	:first_name{ first }, last_name{ last }
{
	if (first_name.size() > first_name_max || last_name.size() > last_name_max)
	{
		throw std::runtime_error("Either your first or last name is too long...");
	}
	for (const auto& target : first_name)
	{
		if ((target < 65 || target > 90) && (target < 97 || target > 122))
		{
			throw std::runtime_error("First name contains an illegal character...");
		}
	}
	for (const auto& target : last_name)
	{
		if ((target < 65 || target > 90) && (target < 97 || target > 122))
		{
			throw std::runtime_error("Last name contains an illegal character...");
		}
	}
}

std::string Author::get_first_name() const
{
	return first_name;
}

std::string Author::get_last_name() const
{
	return last_name;
}