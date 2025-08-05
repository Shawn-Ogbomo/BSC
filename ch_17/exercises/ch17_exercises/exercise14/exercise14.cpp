//14. Could the “list of gods” example from §17.10.1 have been written using a
//singly - linked list; that is, could we have left the prev member out of Link ?
//Why might we want to do that? For what kind of examples would it make
//sense to use a singly - linked list ? Re - implement that example using only a
//singly - linked list.

//Previous member variable may be omitted from Link

//Singly linked-lists required less overhead since prev is removed; their operations are cheaper.
//doubly linked-lists do not allow tail-sharing and cannot be used as persistent data structures.
//singly linked lists are paramount to doubly-linked list when searching is trivial.
#include <iostream>
#include "link.h"

int main() {
	auto* norse_gods = new Link{ "1" };

	norse_gods = norse_gods->add(new Link{ "2" });
	norse_gods = norse_gods->add(new Link{ "3" });
	norse_gods = norse_gods->add(new Link{ "4" });

	norse_gods->advance(3)->add(new Link{ "777" });

	print_all(norse_gods);

	std::cout << "\n\n";

	norse_gods = norse_gods->insert(norse_gods, new Link{ "ZZZZ" });

	norse_gods->advance(3)->insert(norse_gods, new Link{ "BBBB" });

	norse_gods = norse_gods->erase(norse_gods);

	norse_gods = norse_gods->advance(4)->erase(norse_gods);

	print_all(norse_gods);

	std::cout << "\n\n";

	delete norse_gods;
}