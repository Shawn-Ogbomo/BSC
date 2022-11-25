#include <iostream>
#include "date.h"
Date_lib::Date::Date(Year yy, Month mm, int dd)
	:y{ yy }, m{ mm }, d{ dd }
{
	if ((static_cast<int>(m) < static_cast<int>(Month::jan)) || (static_cast<int>(m) > static_cast<int>(Month::dec)) || (d < 1 || d > 31))
	{
		throw std::runtime_error("Invalid date...");
	}
}

bool Date_lib::leapyear(int y)
{
	return y % 4 == 0;
}

int Date_lib::next_workday(const Date& d)		//use Jan not may
{
	if (d.day() % 7 == 0)
	{
		return d.day() + 2;
	}
	else if (d.day() == 31)
	{
		return 1;
	}
	return d.day() + 1;
}

int Date_lib::week_of_the_year(const Date& d)
{
	static Date_lib::Date sample{ 1999, Date_lib::Month::jan, 01 };
	if (d.day())
	{
	}
}