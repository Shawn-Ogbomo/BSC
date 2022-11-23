#include "library.h"
void Library::add_book(const Book& b)
{
	books.push_back(b);
}
void Library::add_patron(const Patron& p)
{
	members.push_back(p);
}
void Library::checkout_book(Patron& member, Book& b, Date_lib::Date d)
{
	for (auto i = 0; i < members.size(); ++i)
	{
		if (member.get_name() == members[i].get_name())
		{
			i = members.size();
			for (const auto& target : books)
			{
				if ((b.get_isbn() == target.get_isbn())
					&& (member.get_fees() == 0) && b.checkout_book())
				{
					Transaction t{ b,member,d };
					t.transactions.push_back(t);
					return;
				}
			}
		}
	}
	std::cerr << "Error: could not check out book...";
}
std::vector<Patron> Library::members_owing()
{
	std::vector<Patron> members_in_debt;
	for (const auto& target : members)
	{
		if (target.get_fees() > 0)
		{
			members_in_debt.push_back(target);
		}
	}
	return members_in_debt;
}
//Library::Transaction::Transaction()
	//:book{}, member{}, date{}
//{
//}

Library::Transaction::Transaction(const Book& b, const Patron& m, const Date_lib::Date& d)
	: book{ b },
	member{ m },
	date{ d }
{
}