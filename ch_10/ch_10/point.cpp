#include <iostream>
#include "point.h"
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
	int val1{};
	int val2{};
	is >> val1 >> val2;
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