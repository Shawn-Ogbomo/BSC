#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iterator>
#include "money.h"
Money::Money()
	:total_cents{},
	currency{}{
}
Money::Money(std::string c, double qty)
	: total_cents{ (static_cast<int>(qty) * 100) },
	currency{ c } {
	for (auto i = 0; i < c.size(); ++i) { currency[i] = std::toupper(currency[i]); }
	if (!currency_ok()) { throw std::runtime_error("Money must have a currency..."); }
	if (qty <= 0) { throw std::runtime_error("Money cannot be zero or a negative value..."); }
	total_cents += std::round((qty - static_cast<int>(qty)) * 100);
}
std::string Money::get_currency() const {
	return currency;
}
Money::operator double() const {
	return (total_cents / static_cast<double>(100));
}
bool Money::currency_ok() const {
	static const std::vector<std::string> valid_currenicies = { "USD","CAD","JPY","NGN", "DKK","CNY" };
	if (!currency.size() || currency.size() > max_currency_size) { return false; }
	auto result = std::find(std::begin(valid_currenicies), std::end(valid_currenicies), currency);
	if (result == std::end(valid_currenicies)) {
		std::cerr << "Invalid currency...\n";
		return false;
	}
	return true;
}
std::istream& operator>>(std::istream& is, Money& m) {
	double amount = 0;
	char symbol = ' ';
	std::string code;
	is >> symbol >> code >> amount;
	if (!is) { return is; }
	if (symbol != '$') {
		is.clear(std::ios_base::failbit);
		return is;
	}
	m = Money(code, amount);
	return is;
}
std::ostream& operator<<(std::ostream& os, const Money& m) {
	return os << '$ ' << static_cast<double>(m);
}
//Money operator+(const Money& left, const Money& right) {
//	return static_cast<double>(left) + static_cast<double>(right);
//}

//Money operator-(const Money& left, const Money& right) {
//	return static_cast<double>(left) - static_cast<double>(right);
//}