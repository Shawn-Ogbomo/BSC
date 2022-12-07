#include <stdexcept>
#include <cmath>
#include "rational.h"
Rational_number::Rational_number(int n, int d)
	: numerator{ n },
	denominator{ d } {
	if (!numerator || !denominator) {
		throw std::runtime_error("Cannot divide by 0...");
	}
}
int Rational_number::get_numerator() const {
	return numerator;
}
int Rational_number::get_denominator() const {
	return denominator;
}
Rational_number::operator double() const {
	return (numerator / static_cast<double>(denominator));
}
void Rational_number::operator=(const Rational_number& right) {
	numerator = right.numerator;
	denominator = right.denominator;
}
Rational_number operator+(const Rational_number& left, const Rational_number& right) {
	Rational_number left_cpy = { left.get_numerator(),left.get_denominator() };
	Rational_number right_cpy = { right.get_numerator(),right.get_denominator() };
	Rational_number result = { left.get_numerator() + right.get_numerator(),left.get_denominator() };
	if (left.get_denominator() < 0) {
		left_cpy = { left.get_numerator() * (-1),left.get_denominator() * (-1) };
	}
	if (right.get_denominator() < 0) {
		right_cpy = { right.get_numerator() * (-1),right.get_denominator() * (-1) };
	}
	if (left_cpy.get_denominator() != right_cpy.get_denominator() && left_cpy.get_denominator() % right_cpy.get_denominator() == 0) {
		double quotient = static_cast<double>(left_cpy.get_denominator()) / right_cpy.get_denominator();
		Rational_number result = { (right_cpy.get_numerator() * static_cast<int>(quotient)) + (left_cpy.get_numerator()) , (right_cpy.get_denominator() * static_cast<int>(quotient)) };
		return result;
	}
	else if (left_cpy.get_denominator() != right_cpy.get_denominator() && right_cpy.get_denominator() % left_cpy.get_denominator() == 0) {
		double quotient = static_cast<double>(right_cpy.get_denominator()) / left_cpy.get_denominator();
		Rational_number result = { (left_cpy.get_numerator() * static_cast<int>(quotient)) + (right_cpy.get_numerator()) , (left_cpy.get_denominator() * static_cast<int>(quotient)) };
		return result;
	}
	else if (left_cpy.get_denominator() != right_cpy.get_denominator()) {
		Rational_number result = { (left_cpy.get_numerator() * right.get_denominator()) + (right_cpy.get_numerator() * left.get_denominator()) , (left_cpy.get_denominator() * right.get_denominator()) };
		return result;
	}
	return result;
}
Rational_number operator*(const Rational_number& left, const Rational_number& right) {
	Rational_number result = { left.get_numerator() * right.get_numerator(), left.get_denominator() * right.get_denominator() };
	if (result.get_denominator() < 0) {
		result = Rational_number{ result.get_numerator() * (-1), result.get_denominator() * (-1) };
		return result;
	}
	return result;
}
Rational_number operator/(const Rational_number& left, const Rational_number& right) {
	Rational_number right_inverted = Rational_number{ right.get_denominator(),right.get_numerator() };
	return left * right_inverted;
}
bool operator==(const Rational_number& left, const Rational_number& right) {
	return left.get_numerator() == right.get_numerator() &&
		left.get_denominator() == right.get_denominator();
}
bool operator!=(const Rational_number& left, const Rational_number& right) {
	return !(left.get_numerator() == right.get_numerator() &&
		left.get_denominator() == right.get_denominator());
}