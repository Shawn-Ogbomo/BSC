#include <iostream>
#include <fstream>
#include "reading.h"
#include "util.h"
void send_to_file(const std::vector<Reading>& r) {
	std::ofstream ofs{ "raw_temps.txt" };
	if (!ofs) {
		std::cerr << "the file does not exist";
		ofs.exceptions(ofs.exceptions() | std::ios_base::badbit);
		return;
	}
	for (const auto& target : r) {
		ofs << target.hour << " " << target.temperature_fahrenheit << "\n";
	}
}
void fill_vector(std::vector<Reading>& r) {			//fix this...
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
		end_of_loop(std::cin, "error", quit);
	}
}
void fill_from_file(std::vector<Reading>& r, const std::string& name) {
	std::ifstream ifs{ name };
	if (!ifs) {
		std::cerr << "the file does not exist";
		ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);
		return;
	}
}
void end_of_loop(std::istream& is, const std::string& message, char term) {
	if (is.bad()) {
		std::cerr << message << "\n";
		is.exceptions(is.exceptions() | std::ios_base::badbit);
		return;
	}
	if (is.fail()) {
		is.clear();
		char c{};
		std::cin >> c;
		if (c != term) {
			is.unget();
			is.clear(std::ios_base::failbit);
		}
	}
}