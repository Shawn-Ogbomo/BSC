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
	:y{ yy },
	m{ mm },
	d{ dd }
{
	if ((!is_date(y, m, d)) || y < min_year)
	{
		throw std::runtime_error("Invalid date...");
	}
	days_since_jan_1_1970 = (((yy - min_year) * (365)) + (static_cast<int>(mm) - static_cast<int>(Month::jan)) * (30.4167) + (dd - static_cast<int>(Day::sunday)));
}
int Chrono::Date::days_in_the_month() const
{
	int days_in_month = 31;
	switch (m)
	{
	case Month::feb:
		days_in_month = leapyear(y) ? 29 : 28;
		break;
	case Month::apr: case Month::jun: case Month::sep: case Month::nov:
		days_in_month = 30;
		break;
	default:
		break;
	}
	return days_in_month;
}
void Chrono::Date::add_month(int n)
{
	const int month_to_int = static_cast<int>(month()) + n;
	if (month_to_int > static_cast<int>(Month::dec))
	{
		m = static_cast<Month>((month_to_int % static_cast<int>(Month::dec)));
		add_year(month_to_int / 12);
		return;
	}
	m = static_cast<Month>(month_to_int);
}
void Chrono::Date::add_year(int n)
{
	y += n;
}
void Chrono::Date::add_day(int n)
{
	d += n;
	while (d > days_in_the_month())
	{
		d -= days_in_the_month();
		add_month(1);
		if (m == Month::jan)
		{
			add_year(1);
		}
	}
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
Chrono::Date Chrono::next_workday(const Date& d)
{
	Date next_w_day = d;
	if (day_of_the_week(next_w_day) == Day::saturday)
	{
		next_w_day.add_day(2);
		return next_w_day;
	}
	else if (day_of_the_week(next_w_day) == Day::friday)
	{
		next_w_day.add_day(3);
		return next_w_day;
	}
	next_w_day.add_day(1);
	return next_w_day;
}
//double Chrono::week_of_the_year(const Date& d)									//fix this...
//{
//	constexpr double weeks_in_month = 4.3;
//	static std::vector<std::vector<int>> ranges
//	{ {1, 2, 3, 4, 5, 6, 7},
//		{ 8,9,10,11,12,13,14 },
//		{ 15,16,17,18,19,20,21 },
//		{ 22,23,24,25,26,27,28 },
//		{ 29,30,31 } };
//	double months_in_weeks = weeks_in_month * (static_cast<int>(d.month()) - 1);
//	for (unsigned int i = 0; i < ranges.size(); ++i)
//	{
//		for (unsigned int j = 0; j < ranges[i].size(); ++j)
//		{
//			if (d.day() == ranges[i][j] && i == (ranges.size() - 1))
//			{
//				return months_in_weeks += weeks_in_month;
//			}
//			if (d.day() == ranges[i][j])
//			{
//				return months_in_weeks += (i + 1);
//			}
//		}
//	}
//}
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

Chrono::Date Chrono::next_sunday(Date& d)
{
	switch (static_cast<int>(day_of_the_week(d)))
	{
	case static_cast<int>(Day::sunday):
		d.add_day(7);
		break;
	case static_cast<int>(Day::monday):
		d.add_day(6);
		break;
	case static_cast<int>(Day::tuesday):
		d.add_day(5);
		break;
	case static_cast<int>(Day::wednesday):
		d.add_day(4);
		break;
	case static_cast<int>(Day::thursday):
		d.add_day(3);
		break;
	case static_cast<int>(Day::friday):
		d.add_day(2);
		break;
	case static_cast<int>(Day::saturday):
		d.add_day(1);
		break;
	default:
		break;
	}
	return d;
}
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