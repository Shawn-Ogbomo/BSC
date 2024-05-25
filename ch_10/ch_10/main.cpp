#include <iostream>
#include <vector>
#include "point.h"
int main() {
	try {
		static constexpr int limit = 7;
		std::cout << "Please enter 7 x, y pairs...\n";
		std::vector<Point>original_points;
		for (Point p; std::cin >> p;) {
			original_points.push_back(p);
			p = Point{};
			if (original_points.size() == limit) {
				std::cout << "\n";
				break;
			}
		}
		display(original_points);
		fill_file(original_points, "mydata.txt");
		std::vector<Point> processsed_points;
		fill_vector(processsed_points, "mydata.txt");
		display(processsed_points);
		compare(original_points, processsed_points);
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << "\n";
		return 1;
	}
	catch (...) {
		std::cout << "exiting....";
		return 2;
	}
}