#include <iostream>
#include <algorithm>
#include <fstream>
#include "reading.h"
#include "util.h"
void send_to_file(const std::vector<Reading>& r) {
	std::ofstream ofs{ "raw_temps.txt" };
	if (!ofs) {
		ofs.exceptions(ofs.exceptions() | std::ios_base::badbit);
		throw std::runtime_error("the file does not exist");
	}

	for (std::size_t i = 0; i < r.size(); ++i) {
		if (i > 0) ofs << '\n';
		ofs << r[i].hour << " " << r[i].temperature_fahrenheit;
	}
}
void fill_vector(std::vector<Reading>& r) {
	while (true) {
		int h = 0;
		double temp_f = 0;
		static char quit = 'q';
		std::cout << "Enter temp readings hour followed by temp. \nWhen finished, press q to stop... \n";
		while (std::cin >> h >> temp_f) {
			if (h < 0 || 23 < h) {
				std::cerr << "Value is out of range try again...\n";
				continue;
			}
			r.push_back(Reading{ h,temp_f });
		}
		Utils::skip_to_int(quit);
		if (std::cin.peek() == quit) {
			return;
		}
		if (std::cin.fail()) {
			throw std::runtime_error("somethings wrong...\nExiting...");
		}
	}
}
void fill_from_file(std::vector<Reading>& r, const std::string& name) {
	std::ifstream ifs{ name };
	if (!ifs) {
		ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);
		throw std::runtime_error("the file does not exist");
	}
	for (Reading temp; ifs >> temp.hour >> temp.temperature_fahrenheit;) {
		r.push_back(temp);
		temp = Reading{};
	}
}

double mode(const std::vector<Reading>& r) {
	if (r.size()) {
		Reading mode;
		int max = 0;
		for (const auto& target : r) {
			int num_items = std::count(r.begin(), r.end(), target);
			if (num_items > max) {
				max = num_items;
				mode = target;
			}
		}
		return mode.temperature_fahrenheit;
	}
	throw std::length_error("The vector is empty...\nNo mode...");
}

bool operator==(const Reading& left, const Reading& right) {
	return (left.temperature_fahrenheit == right.temperature_fahrenheit);
}