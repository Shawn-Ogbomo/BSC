#pragma once
#include <vector>
struct Reading {
	int hour{};
	double temperature_fahrenheit{};
	char code{};
};
void send_to_file(const std::vector<Reading>& r);
void fill_vector(std::vector<Reading>& r);
void fill_from_file(std::vector<Reading>& r, const std::string& name);
double mean(const std::vector<Reading>& r);
double median(const std::vector<Reading>& r);
