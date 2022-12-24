#include <iostream>
#include <fstream>
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
	int val1 = Utils::get_int();
	int val2 = Utils::get_int();
	if (!is) {
		return is;
	}
	p = Point{ val1,val2 };
	return is;
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
	os << p.x_cord() << " " << p.y_cord() << "\n";
	return os;
}

void fill_file(std::vector<Point>& points, const std::string& name) {
	std::ofstream ost{ name };
	if (!ost) {
		std::cerr << "can't open file " << name;
		throw Utils::Invalid{};
	}
	for (const auto& target : points) {
		ost << target;
	}
}