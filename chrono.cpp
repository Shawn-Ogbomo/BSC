#include <iostream>
#include <vector>
#include "chrono.h"
const Chrono::Date& default_date()
{
	static Chrono::Date dd{ 1970,Chrono::Month::jan,1 };
	return dd;
}
Chrono::Date::Date()
	:y{ default_date().year() },
	m{ default_date().month() },
	d{ default_date().day() },
	days_since_jan_1_1970{ }
{
}
Chrono::Date::Date(int yy, Month mm, int dd)
	: y{ yy }, m{ mm }, d{ dd }
{
	if ((!is_date(y, m, d)) || y < min_year)
	{
		throw std::runtime_error("Invalid date...");
	}
	days_since_jan_1_1970 = (((yy - min_year) * (365)) + (static_cast<int>(mm) - static_cast<int>(Month::jan)) * (30.4167) + (dd - static_cast<int>(Day::sunday)));
}
Chrono::Day Chrono::day_of_the_week(const Date& d)
{
	if (d.day() % 7 == 0)
	{
		return Day::saturday;
	}
	else if (d.day() > 7)
	{
		return static_cast<Day>(d.day() % 7);
	}
	return static_cast<Day>(d.day());
}
bool Chrono::leapyear(int yy)
{
	return yy % 4 == 0;
}
int Chrono::next_workday(const Date& d)					 //fix this...
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
double Chrono::week_of_the_year(const Date& d)				//fix this...
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
bool Chrono::is_date(int yy, Month m, int d)
{
	if (d <= 0) return false;
	if (m < Month::jan || Month::dec < m) return false;
	int days_in_month = 31;
	switch (m)
	{
	case Month::feb:
		days_in_month = leapyear(yy) ? 29 : 28;
		break;
	case Month::apr: case Month::jun: case Month::sep: case Month::nov:
		days_in_month = 30;
		break;
	default:
		break;
	}
	if (days_in_month < d) return false;
	return true;
}

//Chrono::Date Chrono::next_sunday(const Date& d)
//{
//}

bool Chrono::operator ==(const Date& a, const Date& b)
{
	return a.year() == b.year()
		&& a.month() == b.month()
		&& a.day() == b.day();
}
bool Chrono::operator !=(const Date& a, const Date& b)
{
	return !(a == b);
}
std::ostream& Chrono::operator <<(std::ostream& os, const Date& d)
{
	return os << '(' << d.year()
		<< ',' << static_cast<int>(d.month())
		<< ',' << d.day() << ')';
}
std::istream& Chrono:: operator >>(std::istream& is, Date& dd)
{
	int y = 0;
	int m = 0;
	int d = 0;
	char ch1 = '?';
	char ch2 = '?';
	char ch3 = '?';
	char ch4 = '?';
	is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
	if (!is) return is;
	if (ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')')
	{
		is.clear(std::ios_base::failbit);
		return is;
	}
	dd = Date(y, Month(m), d);
	return is;
}