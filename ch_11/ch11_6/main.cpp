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
		if (white.find(c) != std::string::npos) {
			return true;
		}

		return false;
	}

	void case_sensitive(bool b) {
		sensitive = b;
	}

	bool is_case_sensitive(bool) const {
		return sensitive;
	}

	Punct_stream& operator >>(std::string& s) {
		while (!(std::getline(buffer,s))) {
			if (buffer.bad() || !source.good()) {
				return *this;
			}

			buffer.clear();
			auto line = ""s;
			std::getline(source, line);

			for (auto& ch : line) {
				if (is_whitespace(ch)) {
					ch = ' ';
				}

				else if (!sensitive) {
					ch = tolower(ch);
				}
			}

			buffer.str(line);
		}
		return *this;
	}

	explicit operator bool() const {
		return !(source.fail() || source.bad() && source.good());
	}

private:
	std::istream& source;
	std::istringstream buffer;
	std::string white;
	bool sensitive{};
};

int main() {
	Punct_stream ps{ std::cin };
	ps.whitespace(".;,?-'");

	std::cout << "Enter a few senteces, .;,?-' will be replaced with a space. Press ctrl-z to exit.\n\n";

	for (auto test{ ""s }; ps >> test;) {
		std::cout <<  test << "\n";
	}

	if (!ps) {
		std::cerr << "Exiting...";
	}
}