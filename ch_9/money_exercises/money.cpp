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
		return Money{ left.currency(), (left.operator double() + static_cast<double>(exchange(left, right))) };
	}
	return Money{ left.currency(), static_cast<double>(left) + static_cast<double>(right) };
}
Money exchange(const Money& left, const Money& right) {
	if (left.currency() == "USD") {
		Exchange_rates::USD american_exchange;
		return Money{ left.currency(),  american_exchange.operator*(right) };
	}
	else if (left.currency() == "CAD") {
		Exchange_rates::CAD canadian_exchange;
		return Money{ left.currency(), canadian_exchange.operator*(right) };
	}
	else if (left.currency() == "JPY") {
		Exchange_rates::JPY japanese_exchange;
		return Money{ left.currency(), japanese_exchange.operator*(right) };
	}
	else if (left.currency() == "NGN") {
		Exchange_rates::NGN nigerian_exchange;
		return Money{ left.currency(),  nigerian_exchange.operator*(right) };
	}
	else if (left.currency() == "DKK") {
		Exchange_rates::DKK danish_exchange;
		return Money{ left.currency(),  danish_exchange.operator*(right) };
	}
	else if (left.currency() == "CNY") {
		Exchange_rates::CNY chinese_exchange;
		return Money{ left.currency(),  chinese_exchange.operator*(right) };
	}
}
Money operator-(const Money& left, const Money& right) {
	if (left.currency() != right.currency()) {
		return exchange(left, right);
	}
	return Money{ left.currency(), static_cast<double>(left) - static_cast<double>(right) };
}
double Exchange_rates::USD::operator*(const Money& m) {
	if (m.currency() == "CAD") {
		return m.operator double() * cad_to_usd;
	}
	else if (m.currency() == "JPY") {
		return m.operator double() * jpy_to_usd;
	}
	else if (m.currency() == "NGN") {
		return m.operator double() * ngn_to_usd;
	}
	else if (m.currency() == "DKK") {
		return m.operator double() * dkk_to_usd;
	}
	else if (m.currency() == "CNY") {
		return m.operator double() * cny_to_usd;
	}
}
double Exchange_rates::CAD::operator*(const Money& m) {
	if (m.currency() == "USD") {
		return m.operator double() * usd_to_cad;
	}
	else if (m.currency() == "JPY") {
		return m.operator double() * jpy_to_cad;
	}
	else if (m.currency() == "NGN") {
		return m.operator double() * ngn_to_cad;
	}
	else if (m.currency() == "DKK") {
		return m.operator double() * dkk_to_cad;
	}
	else if (m.currency() == "CNY") {
		return m.operator double() * cny_to_cad;
	}
}
double Exchange_rates::JPY::operator*(const Money& m) {
	if (m.currency() == "USD") {
		return m.operator double() * usd_to_jpy;
	}
	else if (m.currency() == "CAD") {
		return m.operator double() * cad_to_jpy;
	}
	else if (m.currency() == "NGN") {
		return m.operator double() * ngn_to_jpy;
	}
	else if (m.currency() == "DKK") {
		return m.operator double() * dkk_to_jpy;
	}
	else if (m.currency() == "CNY") {
		return m.operator double() * cny_to_jpy;
	}
}
double Exchange_rates::NGN::operator*(const Money& m) {
	if (m.currency() == "USD") {
		return m.operator double() * usd_to_ngn;
	}
	else if (m.currency() == "CAD") {
		return m.operator double() * cad_to_ngn;
	}
	else if (m.currency() == "JPY") {
		return m.operator double() * jpy_to_ngn;
	}
	else if (m.currency() == "DKK") {
		return m.operator double() * dkk_to_ngn;
	}
	else if (m.currency() == "CNY") {
		return m.operator double() * cny_to_ngn;
	}
}
double Exchange_rates::DKK::operator*(const Money& m) {
	if (m.currency() == "USD") {
		return m.operator double() * usd_to_dkk;
	}
	else if (m.currency() == "CAD") {
		return m.operator double() * cad_to_dkk;
	}
	else if (m.currency() == "JPY") {
		return m.operator double() * jpy_to_dkk;
	}
	else if (m.currency() == "NGN") {
		return m.operator double() * ngn_to_dkk;
	}
	else if (m.currency() == "CNY") {
		return m.operator double() * cny_to_dkk;
	}
}
double Exchange_rates::CNY::operator*(const Money& m) {
	if (m.currency() == "USD") {
		return m.operator double() * usd_to_cny;
	}
	else if (m.currency() == "CAD") {
		return m.operator double() * cad_to_cny;
	}
	else if (m.currency() == "JPY") {
		return m.operator double() * jpy_to_cny;
	}
	else if (m.currency() == "NGN") {
		return m.operator double() * ngn_to_cny;
	}
	else if (m.currency() == "DKK") {
		return m.operator double() * dkk_to_cny;
	}
}