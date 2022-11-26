#pragma once
#include <stdexcept>
namespace Chrono {
	enum class Month
	{
		jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
	};
	class Year
	{
		static constexpr int min = 1970;
		static constexpr int max = 2200;
	public:
		class Invalid {};
		Year() { y = min; }
		Year(int x) : y{ x } { if (x < min || max <= x)  throw Invalid{}; }
		int year() const { return y; };
	private:
		int y;
	};
	class Date
	{
		static constexpr int days_in_a_year = 365;
	public:
		Date();
		Date(Year yy, Month mm, int dd);
		int year() const { return y.year(); }
		Month month() const { return m; }
		int day() const { return d; }
	private:
		Year y;
		Month m;
		int d;
		long int days_since_jan_1_1970;
	};
	bool leapyear(Year y);
	int next_workday(const Date& d);
	double week_of_the_year(const Date& d);
	bool is_date(Year yr, Month m, int d);
	bool operator ==(const Date& a, const Date& b);
	bool operator !=(const Date& a, const Date& b);
	std::ostream& operator <<(std::ostream& os, const Date& d);
	std::istream& operator >>(std::istream& is, Date& dd);
}