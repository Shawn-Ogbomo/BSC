#pragma once
#include <vector>
#include "book.h"
#include "patron.h"
#include "date.h"
struct Transaction
{
	Book book;
	Patron member;
	Date_lib::Date date;
	std::vector<Transaction> transactions;
};
class Library
{
public:

private:
	std::vector<Book> books;
	std::vector<Patron> members;
};