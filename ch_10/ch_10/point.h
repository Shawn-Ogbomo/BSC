#pragma once
#include <vector>
#include <string>
class Point {
public:
	class Invalid {};
	int x_cord() const;
	int y_cord() const;
	Point();
	Point(int coord_x, int coord_y);
private:
	int x;
	int y;
};
bool operator != (const Point& left, const Point& right);
std::istream& operator>>(std::istream& is, Point& p);
std::ostream& operator<<(std::ostream& os, const Point& p);
void fill_file(std::vector<Point>& points, const std::string& name);
void fill_vector(std::vector<Point>& v, const std::string& name);
void display(const std::vector<Point>& points);
bool compare(const std::vector<Point>& left, const std::vector<Point>& right);