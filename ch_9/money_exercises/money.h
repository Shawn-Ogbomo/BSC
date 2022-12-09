#pragma once
class Money {
public:
	Money();
	Money(std::string currency_code, double qty);
	std::string currency() const;
	explicit operator double() const;
	class Invalid {};
private:
	std::string code;
	long int total_cents;
};
std::istream& operator >>(std::istream& is, Money& m);
std::ostream& operator <<(std::ostream& os, const Money& m);
Money operator +(const Money& left, const Money& right);
//Money operator -(const Money& left, const Money& right);