#include "library.h"

void Library::add_book(const Book& b)
{
	books.push_back(b);
}

void Library::add_patron(const Patron& p)
{
	members.push_back(p);
}

void Library::checkout_book(Book& b)
{
	b.checkout_book();
}