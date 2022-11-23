#pragma once
#include <stdexcept>
namespace Date_lib {
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
		Date(Year yy, Month mm, int dd);
		int year() const { return y.year(); }
		Month month() const { return m; }
		int day() const { return d; }
	private:
		Year y;
		Month m;
		int d;
	};
	bool leapyear(int y);
}
