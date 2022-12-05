#include "rational.h"
#include  <stdexcept>
Rational_number::Rational_number(int n, int d)
	: numerator{ n },
	denominator{ d },
	quotient{}{
	if ((numerator == 0) || (numerator < 0 && denominator == 0)) {
		throw std::runtime_error("Cannot divide by 0...");
	}
	quotient = static_cast<double>(n) / d;
}

int Rational_number::get_numerator() const {
	return numerator;
}

int Rational_number::get_denominator() const {
	return denominator;
}

double Rational_number::get_quotient() const {
	return quotient;
}

Rational_number operator+(const Rational_number& lhs, const Rational_number& rhs) {
	double result = lhs.get_quotient() + rhs.get_quotient();
}