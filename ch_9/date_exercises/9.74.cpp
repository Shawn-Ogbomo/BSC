#include <iostream>
#include <stdexcept>
enum class Month
{
	jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};
class Year
{
	static constexpr int min = 1978;
	static constexpr int max = 2200;
public:
	class Invalid {};
	Year(int x) : y{ x } { if (x < min || max <= x)  throw Invalid{}; }
	int year() const { return y; };
	int operator+(int n);
private:
	int y;
};
class Date
{
public:
	Date(Year yy, Month mm, int dd);
	void add_day(int n);
	int year() const { return y.year(); }
	Month month() const { return m; }
	int day() const { return d; }
	void add_month(int n);
	void add_year(int n);
private:
	Year y;
	Month m;
	int d;
};
Date::Date(Year yy, Month mm, int dd)
	:y{ yy }, m{ mm }, d{ dd }
{
	// check that (y,m,d) is a valid date
	if ((static_cast<int>(m) < static_cast<int>(Month::jan)) || (static_cast<int>(m) > static_cast<int>(Month::dec)) || (d < 1 || d > 31))
	{
		throw std::runtime_error("Invalid date...");
	}
}
std::ostream& operator<<(std::ostream& os, const Date& d)
{
	return os << "(" << d.year() << ", " << static_cast<int>(d.month()) << ", " << d.day() << ")" << "\n";
}
void Date::add_day(int n)
{
	if (d < 31)
	{
		d = d + n;
		return;
	}
	throw std::runtime_error("There are 31 days (max) in a month...");
}
void Date::add_month(int n)
{
	int mon = static_cast<int>(m) + n;
	m = static_cast<Month>(mon);
	// add an overload to the month type then you can remove the two lines above...
	if (m > Month::dec)
	{
		throw std::runtime_error("There are only 12 months in a year...");
	}
}
void Date::add_year(int n)
{
	y = y + n;
}
int main()
{
	// 9.74 fix
	try
	{
		Date today{ 1999, Month::nov, 4 };
		Date tomorrow = today;
		tomorrow.add_day(1);
		tomorrow.add_month(1);
		tomorrow.add_year(2);
		std::cout << today << " " << tomorrow;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << "\n";
	}
	catch (...)
	{
		std::cerr << "Invalid year...";
	}
}

int Year::operator+(int n)
{
	return y + n <= max ? y + n : throw Invalid{};
}