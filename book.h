#pragma once
#include <string>
#include<iostream>
#include "date.h"
class Author
{
	static constexpr int first_name_max = 33;
	static constexpr int last_name_max = 17;
public:
	Author(std::string first, std::string last);
	std::string get_first_name()const;
	std::string get_last_name()const;
private:
	std::string first_name;
	std::string last_name;
};
enum class Genre
{
	fiction = 1, nonfiction, periodical, biography, children
};

class Book
{
	static constexpr unsigned int valid_isbn_size = 16;
public:
	std::string get_isbn() const;
	std::string get_title() const;
	std::string get_author() const;
	Genre get_genre() const;
	Date_lib::Date get_copyright_date() const;
	void checkout_book();
	Book(std::string book_isbn, std::string book_name, Author book_author, Date_lib::Date book_copyright_date, Genre book_genre);
private:
	std::string isbn;
	std::string title;
	Author author;
	Date_lib::Date copyright_date;
	Genre genre;
	bool is_valid();
	bool checked_out;
};
bool operator == (const Book& a, const Book& b);
bool operator != (const Book& a, const Book& b);
std::ostream& operator << (std::ostream& os, const Book& a);