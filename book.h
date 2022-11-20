#pragma once
#include <string>
#include "date.h"
class Book
{
public:
	std::string get_isbn() const;
	std::string get_title() const;
	std::string get_author() const;
	Date_lib::Date get_copyright_date() const;
	void checkout_book();
	Book(std::string, std::string, std::string, Date_lib::Date);
private:
	std::string isbn;
	std::string title;
	std::string author;
	Date_lib::Date copyright_date;
	bool is_valid();
	bool checked_out;
};