//#include <iostream>
//#include "token.h"
//Token_gen::Token Token_gen::get(const char c) {
//	switch (c) {
//	case 'I':
//		return Token_gen::Token{ c,1 };
//	case 'V':
//		return Token_gen::Token{ c, 5 };
//	case 'X':
//		return Token_gen::Token{ c, 10 };
//	case 'L':
//		return Token_gen::Token{ c, 50 };
//	case 'C':
//		return Token_gen::Token{ c, 100 };
//	case 'D':
//		return Token_gen::Token{ c, 500 };
//	case 'M':
//		return Token_gen::Token{ c, 1000 };
//	default:
//		throw std::runtime_error{ std::string{c} + " is not a valid roman numeral..." };
//	}
//}
//
//Token_gen::Token::Token() = default;
//
//Token_gen::Token::Token(char c, int v)
//	: roman_letter{ c },
//	val{ v } {
//}
//
//Token_gen::Token::Token(const std::string& s, int v)
//	: val{ v },
//	roman_letters{ s } {
//}