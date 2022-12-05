#pragma once
#include <string>
#include <iostream>
#include "chrono.h"
enum class Genre
{
	fiction = 1, nonfiction, periodical, biography, children
};
class Book
{
	static constexpr unsigned int valid_isbn_size = 16;
	static constexpr int first_name_max = 33;
	static constexpr int last_name_max = 17;
public:
	std::string get_isbn() const;
	std::string get_title() const;
	std::string get_author() const;
	Genre get_genre() const;
	Chrono::Date get_copyright_date() const;
	bool checkout_book();
	Book(std::string book_isbn, std::string book_name, std::string book_author, Chrono::Date book_copyright_date, Genre book_genre);
private:
	std::string isbn;
	std::string title;
	std::string author;
	Chrono::Date copyright_date;
	Genre genre;
	bool checked_out;
};
bool operator == (const Book& a, const Book& b);
bool operator != (const Book& a, const Book& b);
std::ostream& operator << (std::ostream& os, const Book& a);