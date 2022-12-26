#pragma once
#include <vector>
struct Reading {
	int hour{};
	double temperature_fahrenheit{};
};
void send_to_file(const std::vector<Reading>& r);
void fill_vector(std::vector<Reading>& r);
void fill_from_file(std::vector<Reading>& r, const std::string& name);
void end_of_loop(std::istream& is, const std::string& message, char term);