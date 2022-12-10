#pragma once
#include <vector>
#include "book.h"
#include "patron.h"
#include "chrono.h"
class Library
{
public:
	struct Transaction
	{
		Book book;
		Patron member;
		Chrono::Date date;
		Transaction(const Book& b, const Patron& m, const Chrono::Date& d);
		std::vector<Transaction> transactions;
	};
	void add_book(const Book& b);
	void add_patron(const Patron& p);
	void checkout_book(Patron& member, Book& b, Chrono::Date d);
	std::vector<Patron> get_members_owing();
private:
	std::vector<Book> books;
	std::vector<Patron> members;
};