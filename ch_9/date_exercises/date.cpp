#include <iostream>
#include <vector>
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

int Date_lib::next_workday(const Date& d)
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

double Date_lib::week_of_the_year(const Date& d)
{
	constexpr double weeks_in_month = 4.3;
	static std::vector<std::vector<int>> ranges
	{ {1, 2, 3, 4, 5, 6, 7},
		{ 8,9,10,11,12,13,14 },
		{ 15,16,17,18,19,20,21 },
		{ 22,23,24,25,26,27,28 },
		{ 29,30,31 } };
	double months_in_weeks = weeks_in_month * (static_cast<int>(d.month()) - 1);
	for (unsigned int i = 0; i < ranges.size(); ++i)
	{
		for (unsigned int j = 0; j < ranges[i].size(); ++j)
		{
			if (d.day() == ranges[i][j] && i == (ranges.size() - 1))
			{
				return months_in_weeks += weeks_in_month;
			}
			if (d.day() == ranges[i][j])
			{
				return months_in_weeks += (i + 1);
			}
		}
	}
}