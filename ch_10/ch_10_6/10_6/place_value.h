#pragma once
struct Place_value {
	int ones = 0;
	int tens = 0;
	int hundreds = 0;
	int thousands = 0;
	struct Multiplier {
		static constexpr int thousand = 1000;
		static constexpr int hundred = 100;
		static constexpr int ten = 10;
	};
};
