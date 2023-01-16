#pragma once
namespace Token_gen {
	struct Token {
		class Invalid {};
		char roman_letter;
		int val;
		std::string roman_letters;
		Token();
		Token(char c, int v);
		Token(const std::string& s, int v);
	};
	Token get(const char c);
}
