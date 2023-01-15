#include <iostream>
#include "token.h"
Token get(const char c) {
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
	case 'M':
		return Token{ c, 1000 };
	default:
		std::cout << "sorry " << c << " is not a valid roman numeral...\n";
		throw Token::Invalid{};
	}
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