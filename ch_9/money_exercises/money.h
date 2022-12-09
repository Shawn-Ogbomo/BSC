#pragma once
class Money {
	static constexpr int max_currency_size = 3;
public:
	Money();
	Money(std::string currency_code, double qty);
	std::string currency() const;
	long amount() const;
	explicit operator double() const;
	class Invalid {};
private:
	std::string code;
	long total_cents;
};
std::istream& operator >>(std::istream& is, Money& m);
std::ostream& operator <<(std::ostream& os, const Money& m);
Money operator +(const Money& left, const Money& right);
Money exchange(const Money& left, const Money& right);
//Money operator -(const Money& left, const Money& right);
struct Echange_rates {
	struct USD {
		static constexpr double cad_to_usd = 0.73;
		static constexpr double jpy = 136.47;
		static constexpr double ngn = 445.02;
		static constexpr double dkk = 7.06;
		static constexpr double cny = 6.96;
		double operator*(const Money& m);
	};
};
/*struct CAD {
	static constexpr double to_usd = 0.74;
	static constexpr double to_jpy = 100.21;
	static constexpr double to_ngn = 326.79;
	static constexpr double to_dkk = 5.18;
	static constexpr double to_cny = 5.11;
	double operator*(const std::string& c);
};
struct JPY {
	static constexpr double to_usd = 0.0073;
	static constexpr double to_cad = 0.0100;
	static constexpr double to_ngn = 3.26;
	static constexpr double to_dkk = 0.052;
	static constexpr double to_cny = 0.051;
	double operator*(const std::string& c);
};
struct NGN {
	static constexpr double to_usd = 0.0022;
	static constexpr double to_cad = 0.0031;
	static constexpr double to_jpy = 0.31;
	static constexpr double to_dkk = 0.016;
	static constexpr double to_cny = 0.016;
	double operator*(const std::string& c);
};
struct DKK {
	static constexpr double to_usd = 0.14;
	static constexpr double to_cad = 0.19;
	static constexpr double to_jpy = 19.35;
	static constexpr double to_ngn = 63.10;
	static constexpr double to_cny = 1.36;
	double operator*(const std::string& c);
};
struct CNY {
	static constexpr double to_usd = 0.14;
	static constexpr double to_cad = 0.20;
	static constexpr double to_jpy = 19.62;
	static constexpr double to_ngn = 63.96;
	static constexpr double to_dkk = 1.01;
	double operator*(const std::string& c);
};*/
//};
