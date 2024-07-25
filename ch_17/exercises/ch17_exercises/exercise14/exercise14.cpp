//14. Could the “list of gods” example from §17.10.1 have been written using a
//singly - linked list; that is, could we have left the prev member out of Link ?
//Why might we want to do that? For what kind of examples would it make
//sense to use a singly - linked list ? Re - implement that example using only a
//singly - linked list.

//Previous member variable may be omitted from Link

//Using a singly liked-list is suitable when the position of removal is trivial

//singly linked list is suitable when removal and insertion at the back is required

#include <iostream>
#include "link.h"

int main() {
	auto* norse_gods = new Link{ "1" };

	norse_gods->add(new Link{ "2" });
	norse_gods->add(new Link{ "3" });
	norse_gods->add(new Link{ "4" });

	norse_gods->add(new Link{ "Shawn" });

	if (auto* p1{ norse_gods->advance(norse_gods,2) }; p1) {
		p1->add(new Link{ "Shawn7" });
	}

	print_all(norse_gods);

	/*auto* p2{ norse_gods->advance(norse_gods, 2) };

	p2->erase();*/

	norse_gods->erase(norse_gods->advance(norse_gods, 2));

	delete norse_gods;
}