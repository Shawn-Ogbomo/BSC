#include "book.h"
std::string Book::get_isbn() const
{
	return isbn;
}
std::string Book::get_title() const
{
	return title;
}
std::string Book::get_author() const
{
	return author;
}
Genre Book::get_genre() const
{
	return genre;
}
Chrono::Date Book::get_copyright_date() const
{
	return copyright_date;
}
bool Book::checkout_book()
{
	if (!checked_out)
	{
		checked_out = true;
		return true;
	}
	std::cout << "The book: " << get_title() << " has already been checked out. Please try checking out another book instead if interested\n";
	return false;
}
Book::Book(std::string book_isbn, std::string book_name, std::string book_author, Chrono::Date book_copyright_date, Genre book_genre)
	:isbn{ book_isbn },
	title{ book_name },
	author{ book_author },
	copyright_date{ book_copyright_date },
	genre{ book_genre },
	checked_out{ false }
{
	if ((isbn.size() == valid_isbn_size) && (std::count(isbn.begin(), isbn.end(), '-') == 3) && (genre <= Genre::children) && std::count(author.begin(), author.end(), ' ') == 1 && (author.size() < first_name_max + last_name_max))
	{
		for (unsigned int i = 0, count = 1; (i < valid_isbn_size) && (isdigit(isbn[i]) && isalpha(isbn.back())); ++i, ++count)
		{
			if ((count % 4 == 0) && (isbn[i + 1] == '-'))
			{
				++i;
			}
		}
		if ((!isdigit(isbn.back())) && (!isalpha(isbn.back())))
		{
			throw std::runtime_error("Invalid character in isbn...");
		}
		for (const auto& target : author)
		{
			if (!isalpha(target) && !isspace(target))
			{
				throw std::runtime_error("invalid name...");
			}
		}
	}
}
bool operator==(const Book& a, const Book& b)
{
	return a.get_isbn() == b.get_isbn();
}
bool operator!=(const Book& a, const Book& b)
{
	return a.get_isbn() != b.get_isbn();
}
std::ostream& operator<<(std::ostream& os, const Book& a)
{
	return os
		<< a.get_title()
		<< "\n"
		<< a.get_author()
		<< "\n"
		<< a.get_isbn()
		<< "\n"
		<< static_cast<int>(a.get_genre())
		<< "\n\n";
}