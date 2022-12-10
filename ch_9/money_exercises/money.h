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
struct Exchange_rates {
	struct USD {
		static constexpr double cad_to_usd = 0.7285178304739;
		static constexpr double jpy_to_usd = 0.0073225199900779;
		static constexpr double ngn_to_usd = 0.0022473425174731;
		static constexpr double dkk_to_usd = 0.14160094023024;
		static constexpr double cny_to_usd = 0.14372359079019;
		double operator*(const Money& m);
	};

	struct CAD {
		static constexpr double usd_to_cad = 1.37265;
		static constexpr double jpy_to_cad = 0.01005125706438;
		static constexpr double ngn_to_cad = 0.0030848147066094;
		static constexpr double dkk_to_cad = 0.19436853060704;
		static constexpr double cny_to_cad = 0.19728218689816;
		double operator*(const Money& m);
	};
	struct JPY {
		static constexpr double usd_to_jpy = 136.56500786;
		static constexpr double cad_to_jpy = 99.490043244818;
		static constexpr double ngn_to_jpy = 0.30690834856282;
		static constexpr double dkk_to_jpy = 19.337733515527;
		static constexpr double cny_to_jpy = 19.62761330593;
		double operator*(const Money& m);
	};
	struct NGN {
		static constexpr double usd_to_ngn = 444.97;
		static constexpr double cad_to_ngn = 324.16857902597;
		static constexpr double jpy_to_ngn = 3.258301719985;
		static constexpr double dkk_to_ngn = 63.008170374251;
		static constexpr double cny_to_ngn = 63.952686193912;
		double operator*(const Money& m);
	};
	struct DKK {
		static constexpr double usd_to_dkk = 7.0621;
		static constexpr double cad_to_dkk = 5.1448657705897;
		static constexpr double jpy_to_dkk = 0.051712368421929;
		static constexpr double ngn_to_dkk = 0.015870957592647;
		static constexpr double cny_to_dkk = 1.0149903705194;
		double operator*(const Money& m);
	};
	struct CNY {
		static constexpr double usd_to_cny = 6.9578;
		static constexpr double cad_to_cny = 5.0688813608713;
		static constexpr double jpy_to_cny = 0.050948629586964;
		static constexpr double ngn_to_cny = 0.015636559768074;
		static constexpr double dkk_to_cny = 0.98523102193399;
		double operator*(const Money& m);
	};
};
