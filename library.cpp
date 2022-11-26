#include "library.h"
void Library::add_book(const Book& b)
{
	books.push_back(b);
}
void Library::add_patron(const Patron& p)
{
	members.push_back(p);
}
void Library::checkout_book(Patron& member, Book& b, Chrono::Date d)
{
	for (auto i = 0; i < members.size(); ++i)
	{
		if (member.get_name() == members[i].get_name())
		{
			i = members.size();
			for (const auto& target : books)
			{
				if ((b.get_isbn() == target.get_isbn())
					&& (!in_debt(member)) && b.checkout_book())
				{
					Transaction t{ b,member,d };
					t.transactions.push_back(t);
					std::cout << member.get_name() << " has checked out: \n" << b << "\n";
					return;
				}
			}
		}
	}
	std::cerr << "Error: " << member.get_name() << " could not check out book...\n" << b;
}
std::vector<Patron> Library::get_members_owing()
{
	std::vector<Patron> members_in_debt;
	for (const auto& target : members)
	{
		if (in_debt(target))
		{
			members_in_debt.push_back(target);
		}
	}
	return members_in_debt;
}

Library::Transaction::Transaction(const Book& b, const Patron& m, const Chrono::Date& d)
	: book{ b },
	member{ m },
	date{ d }
{
}