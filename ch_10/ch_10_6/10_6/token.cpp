#include <iostream>
#include "token.h"
Token_stream::Token_stream() :buffer{},
full{ false } {
}
Token Token_stream::get(const char c) {
	if (full) {
		full = false;
		return buffer;
	}
	switch (c) {
	case 'I':
		return Token{ c,1 };
	case 'V':
		return Token{ c, 5 };
	case 'X':
		return Token{ c, 10 };
	case 'L':
		return Token{ c, 50 };
	case 'C':
		return Token{ c, 100 };
	case 'D':
		return Token{ c, 500 };
		//case 'M':
		//	return Token{ c, 1000 };
	default:
		std::cout << "sorry " << c << " is not a valid roman numeral...\n";
		throw Token::Invalid{};
	}
}

void Token_stream::put_back(Token t) {
	if (full) {
		std::cerr << "cannot put a token into a stream that is already full...\n";
		throw Token::Invalid{};
	}
	buffer = t;
	full = true;
}

Token::Token()
	:roman_letter{},
	val{},
	roman_letters{} {
}

Token::Token(char c, int v) : roman_letter{ c },
val{ v },
roman_letters{}{
}

Token::Token(const std::string& s, int v) : roman_letters{ s },
val{ v },
roman_letter{} {
}