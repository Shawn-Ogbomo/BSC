#pragma once
class Rational_number
{
public:
	Rational_number(int n, int d);
	int get_numerator() const;
	int get_denominator() const;
	operator double();
	void operator =(const Rational_number& right);
private:
	int numerator;
	int denominator;
};
Rational_number operator +(const Rational_number& left, const Rational_number& right);
bool operator == (const Rational_number& left, const Rational_number& right);
bool operator != (const Rational_number& left, const Rational_number& right);
