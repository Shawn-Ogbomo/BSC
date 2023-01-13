#pragma once
struct Token {
	class Invalid {};
	char roman_letter;
	int val;
	std::string roman_letters;
	Token();
	Token(char c, int v);
	Token(const std::string& s, int v);
};
class Token_stream {
public:
	Token_stream();
	Token get(const char c);
	void put_back(Token t);
private:
	Token buffer;
	bool full;
};