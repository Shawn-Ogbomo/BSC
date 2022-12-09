#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iterator>
#include "money.h"
Money::Money()
	:total_cents{},
	code{}{
}
Money::Money(std::string currency_code, double qty)
	: total_cents{ (static_cast<int>(qty) * 100) },
	code{ currency_code } {
	static const std::vector<std::string> valid_currenicies = { "USD","CAD","JPY","NGN", "DKK","CNY" };
	if (currency_code.size() > max_currency_size) {
		std::cerr << "Exceeded character limit...\nCurrencies are 3 letters long...\n";
		throw Invalid{};
	}
	for (auto i = 0; i < code.size(); ++i) {
		code[i] = std::toupper(code[i]);
	}
	auto result = std::find(std::begin(valid_currenicies), std::end(valid_currenicies), code);
	if (result == std::end(valid_currenicies)) {
		std::cerr << "Invalid currency...\n";
		throw Invalid{};
	}
	if (qty <= 0) {
		std::cerr << "Money cannot be zero or a negative value...\n";
		throw Invalid{};
	}
	total_cents += std::round((qty - static_cast<int>(qty)) * 100);
	if (total_cents <= 0) {
		std::cerr << "The value is too large....\n";
		throw Invalid{};
	}
}
std::string Money::currency() const {
	return code;
}
long Money::amount() const {
	return total_cents;
}
Money::operator double() const {
	return (total_cents / static_cast<double>(100));
}
std::istream& operator>>(std::istream& is, Money& m) {
	double amount = 0;
	char symbol{};
	std::string code;
	is >> symbol >> code >> amount;
	if (!is) {
		return is;
	}
	if (symbol != '$') {
		is.clear(std::ios_base::failbit);
		return is;
	}
	m = Money(code, amount);
	return is;
}
std::ostream& operator<<(std::ostream& os, const Money& m) {
	return os << "$" << static_cast<double>(m);
}
Money operator+(const Money& left, const Money& right) {
	if (left.currency() != right.currency()) {
		return exchange(left, right);
	}
	return Money{ left.currency(), static_cast<double>(left) + static_cast<double>(right) };
}
Money exchange(const Money& left, const Money& right) {
	if (left.currency() == "USD") {
		Echange_rates::USD american_exchange;
		return Money{ left.currency(), left.operator double() + american_exchange.operator*(right) };
	}
}
//Money operator-(const Money& left, const Money& right) {
//	return static_cast<double>(left) - static_cast<double>(right);
//}
double Echange_rates::USD::operator*(const Money& m) {
	if (m.currency() == "CAD") {
		std::cout << m.operator double() * cad_to_usd;
		return m.operator double() * cad_to_usd;
	}
	else if (m.currency() == "JPY") {}
	else if (m.currency() == "NGN") {}
	else if (m.currency() == "DKK") {}
	else if (m.currency() == "CNY") {}
}