#pragma once
#include <string>
#include <stdexcept>
class Patron
{
	static constexpr int first_name_max = 12;
	static constexpr int last_name_max = 12;
public:
	Patron(std::string member_name, std::string member_card_number);
	std::string get_name() const;
	std::string get_card_number() const;
	double get_fees() const;

private:
	std::string name;
	std::string card_number;
	double fees;
	bool in_debt;
	bool is_valid();
};
bool debt(const Patron& member);