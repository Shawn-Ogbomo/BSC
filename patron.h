#pragma once
#include <string>
class Patron
{
	static constexpr int first_name_max = 12;
	static constexpr int last_name_max = 12;
public:
	Patron(std::string member_name, std::string member_card_number);
	Patron(std::string member_name, std::string member_card_number, double debt);
	std::string get_name() const;
	std::string get_card_number() const;
	double get_fees() const;
private:
	std::string name;
	std::string card_number;
	double fees;
	bool is_valid();
};
bool in_debt(const Patron& member);