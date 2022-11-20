#include <stdexcept>
#include "date.h"
Date_lib::Date::Date(Year yy, Month mm, int dd)
	:y{ yy }, m{ mm }, d{ dd }
{
	if ((static_cast<int>(m) < static_cast<int>(Month::jan)) || (static_cast<int>(m) > static_cast<int>(Month::dec)) || (d < 1 || d > 31))
	{
		throw std::runtime_error("Invalid date...");
	}
}