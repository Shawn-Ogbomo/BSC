#include "point.h"
Point::Point()
	: x{},
	y{} {
}

Point::Point(int coord_x, int coord_y)
	: x{ coord_x },
	y{ coord_y } {
}