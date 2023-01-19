#pragma once
namespace Token_gen {
	struct Token {
		class Invalid {
		public:
			Invalid(const std::string& err) :error_message{ err } {}
			std::string what() { return error_message; }
		private:
			std::string error_message;
		};
		char roman_letter;
		int val;
		std::string roman_letters;
		Token();
		Token(char c, int v);
		Token(const std::string& s, int v);
	};
	Token get(const char c);
}