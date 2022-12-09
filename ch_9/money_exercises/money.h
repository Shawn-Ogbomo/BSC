#pragma once
class Money {
	static constexpr int max_currency_size = 3;
public:
	Money();
	Money(std::string c, double qty);
	std::string currency() const;
	explicit operator double() const;
private:
	bool currency_ok()const;
	std::string code;
	long int total_cents;
};
std::istream& operator >>(std::istream& is, Money& m);
std::ostream& operator <<(std::ostream& os, const Money& m);
Money operator +(const Money& left, const Money& right);
//Money operator -(const Money& left, const Money& right);