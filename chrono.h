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
		static constexpr int min_year = 1970;
	public:
		Date();
		Date(int yy, Month mm, int dd);
		int year() const { return y; }
		Month month() const { return m; }
		int day() const { return d; }
		int days_in_the_month()const;
		void add_month(int n);
		void add_year(int n);
		void add_day(int n);
	private:
		int y;
		Month m;
		int d;
		long int days_since_jan_1_1970;
		void update_days_since_1970();
	};
	bool leapyear(int yy);
	int week_of_the_year(const Date& d);
	bool is_date(int yy, Month m, int d);
	Chrono::Day day_of_the_week(const Date& d);
	Date next_workday(const Date& d);
	Date next_sunday(Date& d);
	bool operator ==(const Date& a, const Date& b);
	bool operator !=(const Date& a, const Date& b);
	std::ostream& operator <<(std::ostream& os, const Date& d);
	std::istream& operator >>(std::istream& is, Date& dd);
}