#include<iostream>
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

Book::Book(std::string book_isbn, std::string book_name, std::string book_author, Date_lib::Date book_copyright_date)
	:isbn{ book_isbn },
	title{ book_name },
	author{ book_author },
	copyright_date{ book_copyright_date },
	checked_out{ false }
{
	if (!is_valid())
	{
		throw std::runtime_error("isbn or author is in invalid format...");
	}
}

bool Book::is_valid()
{
	for (const auto& target : author)
	{
		if ((target < 65 || target > 90) && (target < 97 || target > 122) && (!isspace(target)))
		{
			return false;
		}
	}
}