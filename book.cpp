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
	return author.get_first_name() + " " + author.get_last_name();
}

Genre Book::get_genre() const
{
	return genre;
}

Date_lib::Date Book::get_copyright_date() const
{
	return copyright_date;
}

void Book::checkout_book()
{
	if (!checked_out)
	{
		checked_out = true;
		return;
	}
	std::cout << "The book: " << get_title() << " has already been checked out. Please try checking out another book instead if interested";
}

Book::Book(std::string book_isbn, std::string book_name, Author book_author, Date_lib::Date book_copyright_date, Genre book_genre)
	:isbn{ book_isbn },
	title{ book_name },
	author{ book_author },
	copyright_date{ book_copyright_date },
	genre{ book_genre },
	checked_out{ false }
{
	if (!is_valid())
	{
		throw std::runtime_error("isbn is in invalid format...");
	}
}

bool Book::is_valid()
{
	if ((isbn.size() == valid_isbn_size) && (std::count(isbn.begin(), isbn.end(), '-') == 3) && (genre <= Genre::children))
	{
		for (unsigned int i = 0, count = 1; (i < valid_isbn_size) && (isdigit(isbn[i]) || isalpha(isbn.back())); ++i, ++count)
		{
			if (count % 4 == 0 && (isbn[i + 1] == '-'))
			{
				++i;
			}
			else if (i == (valid_isbn_size - 1))
			{
				return true;
			}
		}
	}
	return false;
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
		<< static_cast<int>(a.get_genre());
}