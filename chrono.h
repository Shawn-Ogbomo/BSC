#pragma once
#include <stdexcept>
namespace Chrono {
	enum class Month
	{
		jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
	};
	enum class Day
	{
		sunday = 1, monday, tuesday, wednesday, thursday, friday, saturday
	};
	class Date
	{
	public:
		Date();
		Date(int yy, Month mm, int dd);
		int year() const { return y; }
		Month month() const { return m; }
		int day() const { return d; }
	private:
		int y;
		Month m;
		int d;
		long int days_since_jan_1_1970;
	};
	bool leapyear(int yy);
	int next_workday(const Date& d);
	double week_of_the_year(const Date& d);
	bool is_date(int yy, Month m, int d);
	Chrono::Day day_of_the_week(const Date& d);
	bool operator ==(const Date& a, const Date& b);
	bool operator !=(const Date& a, const Date& b);
	std::ostream& operator <<(std::ostream& os, const Date& d);
	std::istream& operator >>(std::istream& is, Date& dd);
}