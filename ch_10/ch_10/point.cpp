#include <iostream>
#include "point.h"
#include "util.h"
int Point::x_cord() const {
	return x;
}
int Point::y_cord() const {
	return y;
}
Point::Point()
	: x{},
	y{} {
}

Point::Point(int coord_x, int coord_y)
	: x{ coord_x },
	y{ coord_y } {
}

std::istream& operator>>(std::istream& is, Point& p) {
	int val1 = Utils::get_int(0, 1000, "Enter a value from", "out or range");
	int val2 = Utils::get_int(0, 1000, "Enter a value from", "out or range");
	if (!is) {
		return is;
	}
	p = Point{ val1,val2 };
	return is;
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
	os << p.x_cord() << " " << p.y_cord();
	return os;
}