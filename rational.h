#pragma once
class Rational_number
{
public:
	Rational_number(int n, int d);
	int get_numerator() const;
	int get_denominator() const;
	double get_quotient() const;
private:
	int numerator;
	int denominator;
	double quotient;
};
Rational_number operator +(const Rational_number& lhs, const Rational_number& rhs);