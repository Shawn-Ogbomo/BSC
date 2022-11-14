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
private:
	int y;
};
class Date
{
public:
	Date(Year yy, int mm, int dd);
	void add_day(int n);
	int year() const { return y.year(); }
	int month() const { return m; }
	int day() const { return d; }
private:
	Year y;
	int m;
	int d;
};
Date::Date(Year yy, int mm, int dd)
	:y{ yy }, m{ mm }, d{ dd }
{
	// check that (y,m,d) is a valid date
	if ((m < static_cast<int>(Month::jan)) || (m > static_cast<int>(Month::dec)) || (d < 1 || d > 31))
	{
		throw std::runtime_error("Invalid date...");
	}
}
std::ostream& operator<<(std::ostream& os, const Date& d)
{
	return os << "(" << d.year() << ", " << d.month() << ", " << d.day() << ")" << "\n";
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
int main()
{
	// define a Date called today initialized to June 25 1978
	// define a Date called tomorrow and give it a value by copying today into it and increasing its day by one using add_day().
	// finally output today and tomorrow using a << defined in 9.8
	try
	{
		Date today{ 1999, 5, 4 };
		Date tomorrow = today;
		tomorrow.add_day(1);
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