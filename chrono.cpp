#include <iostream>
#include <vector>
#include <cmath>
#include "chrono.h"
const Chrono::Date& default_date() {
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
	d{ dd },
	days_since_jan_1_1970{ }
{
	if ((!is_date(y, m, d))) {
		throw std::runtime_error("Invalid date...");
	}
	update_days_since_1970();
}

int Chrono::Date::days_in_the_month() const {
	int days_in_month = 31;
	switch (m) {
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
void Chrono::Date::add_month(int n) {
	const int month_to_int = static_cast<int>(month()) + n;
	if (month_to_int > static_cast<int>(Month::dec)) {
		m = static_cast<Month>((month_to_int % static_cast<int>(Month::dec)));
		add_year(month_to_int / 12);
		return;
	}
	m = static_cast<Month>(month_to_int);
}
void Chrono::Date::add_year(int n) {
	y += n;
}
void Chrono::Date::add_day(int n) {
	d += n;
	while (d > days_in_the_month()) {
		d -= days_in_the_month();
		add_month(1);
		if (m == Month::jan) {
			add_year(1);
		}
	}
}
void Chrono::Date::update_days_since_1970() {
	const int target_year_cpy = y;
	const int month_cpy = static_cast<int>(m);
	y = min_year;
	m = Month::jan;
	if (target_year_cpy == min_year && m < static_cast<Month>(month_cpy)) {
		for (auto i = 0; i < static_cast<int>(month_cpy) - 1; ++i, ++m) {
			days_since_jan_1_1970 += days_in_the_month();
		}
		days_since_jan_1_1970 += (d - 1);
		return;
	}
	while ((y < target_year_cpy)) {
		for (auto i = 0; i < static_cast<int>(Month::dec); ++i, ++m) {
			days_since_jan_1_1970 += days_in_the_month();
		}
		++y;
		if (y == target_year_cpy) {
			for (auto i = 0; i < (static_cast<int>(month_cpy) - 1); ++i, ++m) {
				days_since_jan_1_1970 += days_in_the_month();
			}
		}
	}
	days_since_jan_1_1970 += (d - 1);
}
Chrono::Day Chrono::day_of_the_week(const Date& d) {
	if (d.day() % 7 == 0) {
		return Day::saturday;
	}
	else if (d.day() > 7) {
		return static_cast<Day>(d.day() % 7);
	}
	return static_cast<Day>(d.day());
}
Chrono::Month Chrono::operator++(Month& m) {
	return m = (m == Month::dec) ? Month::jan : static_cast<Month>(static_cast<int>(m) + (1));
}
bool Chrono::leapyear(int yy) {
	return (yy % 4 == 0) && (yy % 100 == 0) && (yy % 400 == 0) ||
		(yy % 4 == 0) && (yy % 100 != 0);
}
Chrono::Date Chrono::next_workday(const Date& d) {
	Date current_w_day = d;
	if (day_of_the_week(current_w_day) == Day::saturday) {
		current_w_day.add_day(2);
		return current_w_day;
	}
	else if (day_of_the_week(current_w_day) == Day::friday) {
		current_w_day.add_day(3);
		return current_w_day;
	}
	current_w_day.add_day(1);
	return current_w_day;
}
int Chrono::week_of_the_year(const Date& d) {
	Date first_day_of_year{ d.year(),Month::jan,1 };
	double week_in_year = 0;
	while (first_day_of_year.month() < d.month()) {
		week_in_year += (first_day_of_year.days_in_the_month() / static_cast<double>(7));
		first_day_of_year.add_month(1);
		if (first_day_of_year.month() == d.month()) {
			week_in_year += d.day() / static_cast<double>(7);
			return std::round(week_in_year);
		}
	}
	return std::round(d.day() / static_cast<double>(7));
}
bool Chrono::is_date(int yy, Month m, int d) {
	if (yy < 1970) return false;
	if (d <= 0) return false;
	if (m < Month::jan || Month::dec < m) return false;
	int days_in_month = 31;
	switch (m) {
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
Chrono::Date Chrono::next_sunday(Date& d) {
	switch (static_cast<int>(day_of_the_week(d))) {
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
bool Chrono::operator ==(const Date& a, const Date& b) {
	return a.year() == b.year()
		&& a.month() == b.month()
		&& a.day() == b.day();
}
bool Chrono::operator !=(const Date& a, const Date& b) {
	return !(a == b);
}
std::ostream& Chrono::operator <<(std::ostream& os, const Date& d) {
	return os << '(' << d.year()
		<< ',' << static_cast<int>(d.month())
		<< ',' << d.day() << ')';
}
std::istream& Chrono:: operator >>(std::istream& is, Date& dd) {
	int y = 0;
	int m = 0;
	int d = 0;
	char ch1 = '?';
	char ch2 = '?';
	char ch3 = '?';
	char ch4 = '?';
	is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
	if (!is) return is;
	if (ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')') {
		is.clear(std::ios_base::failbit);
		return is;
	}
	dd = Date(y, Month(m), d);
	return is;
}