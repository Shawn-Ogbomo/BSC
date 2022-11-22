#pragma once
#include <vector>
#include "book.h"
#include "patron.h"
#include "date.h"
class Library
{
public:
	struct Transaction
	{
		Book book;
		Patron member;
		Date_lib::Date date;
		std::vector<Transaction> transactions;
	};
	void add_book(const Book& b);
	void add_patron(const Patron& p);
	void checkout_book(Book& b);
private:
	std::vector<Book> books;
	std::vector<Patron> members;
};