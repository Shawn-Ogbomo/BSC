#pragma once
struct Reading {
	int sum{};
	class Invalid {};
};
void total_from_file(Reading& r, const std::string& file_name);
