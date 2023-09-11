#include <iostream>
#include <string_view>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

using namespace std::string_literals;
//Write a program that replaces punctuation with whitespace.Consider
//. (dot), ; (semicolon), , (comma), ? (question mark), -(dash), ' (single
//quote) punctuation characters.Don’t modify characters within a pair of
//double quotes("). For example, “ - don't use the as-if rule.” becomes
//	“ don t use the as if rule ”.

class Punct_stream {
public:
	explicit Punct_stream(std::istream& is)
		:source{ is }
		, sensitive{ true } {
	}

	void whitespace(std::string_view s) {
		white = s;
	}

	void add_white(char c) {
		white += c;
	}

	bool is_whitespace(char c) const {
	}

	void case_sensitive(bool b) {
		sensitive = b;
	}

	bool is_case_sensitive(bool) const {
		return sensitive;
	}

	friend std::istream& operator >>(std::istream& is, Punct_stream& p) {
	}

	explicit operator bool() const {
	}
private:
	std::istream& source;
	std::istringstream buffer;
	std::string white;
	bool sensitive{};
};

int main() {
}