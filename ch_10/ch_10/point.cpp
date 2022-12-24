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

bool operator!=(const Point& left, const Point& right) {
	return !(left.x_cord() == right.x_cord() &&
		left.y_cord() == right.y_cord());
}

std::istream& operator>>(std::istream& is, Point& p) {
	int val1 = Utils::get_int(is);
	int val2 = Utils::get_int(is);
	if (!is) {
		if (is.bad()) {
			is.exceptions(is.exceptions() | std::ios_base::badbit);
		}
	}
	p = Point{ val1,val2 };
	return is;
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
	os << p.x_cord() << " " << p.y_cord();
	return os;
}

void fill_file(std::vector<Point>& points, const std::string& name) {
	std::ofstream ost{ name };
	if (!ost) {
		std::cerr << "can't open file " << name;
		ost.exceptions(ost.exceptions() | std::ios::badbit);
	}
	for (int i = 0; i < points.size(); ++i) {
		ost << points[i];
		if (i < points.size() - 1) {
			ost << "\n";
		}
	}
}

void fill_vector(std::vector<Point>& v, const std::string& name) {
	std::ifstream ist{ name };
	if (!ist) {
		std::cerr << "can't open file " << name;
		ist.exceptions(ist.exceptions() | std::ios::badbit);
	}
	for (Point p; ist >> p;) {
		v.push_back(p);
		p = Point{};
		if (ist.eof()) {
			return;
		}
	}
}

void display(const std::vector<Point>& points) {
	if (points.size()) {
		for (const auto& target : points) {
			std::cout << target << "\n";
		}
		std::cout << "\n";
		return;
	}
	throw std::length_error("You don't have any points...");
}

bool compare(const std::vector<Point>& left, const std::vector<Point>& right) {
	if ((left.size() != right.size()) || (!left.size()) || (!right.size())) {
		std::cerr << "Somethings wrong...";
		return false;
	}
	if (left.size() == right.size()) {
		for (int i = 0; i < left.size(); ++i) {
			if (left[i] != right[i]) {
				std::cerr << "Somethings wrong...";
				return false;
			}
		}
	}
	std::cout << "The vectors are identical...";
	return true;
}