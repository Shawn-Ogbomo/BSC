//  Use the program from the previous exercise to make a dictionary(as an
//	alternative to the approach in §11.7).Run the result on a multi - page text
//	file, look at the result, and see if you can improve the program to make a
//	better dictionary

#include <iostream>
#include <string_view>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std::string_literals;

class Punct_stream {
public:
	explicit Punct_stream(std::istream& is)
		:source{ is }
		, sensitive{ true } {
	}

	void whitespace(std::string_view s)
	{
		white = s;
	}

	void add_white(char c) {
		white += c;
	}

	bool is_whitespace(char c) const
	{
		if (white.find(c) != std::string::npos)
		{
			return true;
		}

		return false;
	}

	void case_sensitive(bool b)
	{
		sensitive = b;
	}

	bool is_case_sensitive(bool) const
	{
		return sensitive;
	}

	//REPLACES NEGATIVE CONTRACTIONS WITH THEIR EXPANDED FORMS...
	void replace_contractions(std::string& s) const
	{
		static const std::map<std::string, std::string> english_negative_contractions{
		{"can't","cannot"},{"don't","do not"}, {"won't","will not"},
		{"isn't","is not"},{"wouldn't", "will not"}, {"shouldn't","should not"},
			{"couldn't","could not"}, {"aren't","are not"}, {"doesn't", "does not"},
			{"wasn't","was not"}, {"weren't","were not" }, {"hasn't","has not"}, {"haven't" ,"have not"},
			{"hadn't", "had not"},{"mustn't","must not"},{"didn't", "did not"}, {"mightn't","might not"},
			{"needn't","need not"}
		};

		std::for_each(english_negative_contractions.begin(), english_negative_contractions.end(), [&s](std::pair<std::string, std::string> const& contraction) {
			if (auto pos = s.find(contraction.first); pos != std::string::npos)
			{
				s.replace(pos, contraction.first.size(), contraction.second);
			}
			});
	}

	Punct_stream& operator >>(std::string& s)
	{
		while (!(std::getline(buffer, s)))
		{
			if (buffer.bad() || !source.good())
			{
				return *this;
			}

			buffer.clear();
			auto line = ""s;
			std::getline(source, line);

			for (auto& ch : line)
			{
				if (is_whitespace(ch))
				{
					ch = ' ';
				}

				else if (!sensitive)
				{
					ch = static_cast<char>(tolower(ch));
				}
			}

			replace_contractions(line);

			buffer.str(line);
		}
		return *this;
	}

	explicit operator bool() const
	{
		return !(source.fail() || source.bad() && source.good());
	}

private:
	std::istream& source;
	std::istringstream buffer;
	std::string white;
	bool sensitive{};
};

int main()
{
	Punct_stream ps{ std::cin };
	ps.whitespace(";,?");

	std::cout << "Enter a few sentences, contractions will be replaced with their expanded form. Press ctrl-z to exit.\n\n";

	for (auto test{ ""s }; ps >> test;)
	{
		std::cout << test << "\n";
		//push each word to words vector
			//prevent duplicates
			//remove punctuation characters from word
	}

	//function to display words vector

	if (!ps)
	{
		std::cerr << "Exiting...";
	}
}