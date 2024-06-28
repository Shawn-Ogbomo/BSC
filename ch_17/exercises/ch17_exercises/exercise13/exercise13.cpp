//13. Modify the Link class from §17.10.1 to hold a value of a struct God.
//struct God should have members of type string : name, mythology, vehicle,
//	and weapon.For example, God{ "Zeus", "Greek", "", "lightning" }
//	and God{ "Odin", "Norse", "Eight-legged flying horse called Sleipner",
//	"Spear called Gungnir" }. Write a print_all() function that lists gods with
//their attributes one per line.Add a member function add_ordered() that
//places its new element in its correct lexicographical position.Using the
//Links with the values of type God, make a list of gods from three mythologies;
//then move the elements(gods) from that list to three lexicographically
//ordered lists — one for each mythology.
#include <iostream>
#include "link.h"

//static const Link* ordered_list(const Link* lhs, Link* rhs) {
//	if (!lhs)
//	{
//		return nullptr;
//	}
//
//	if (!rhs)
//	{
//		return lhs;
//	}
//
//	//GET FIRST INDEX OF LHS
//	//auto* p1{ const_cast<Link*>(lhs)->first_index() };
//
//	//TRAVERSE LHS USING NEXT
//		//RECURSIVE CALL TO ADD_ORDERED INTO RHS
//
//	return p1;
//}

int main() {
	auto* norse_gods = new Link{ God{"Odin","Greek","...",""} };

	norse_gods = norse_gods->insert(new Link{ God{"Frigg","Norse","...",""} });
	norse_gods = norse_gods->insert(new Link{ God{"Loki","Norse","...",""} });
	norse_gods = norse_gods->insert(new Link{ God{"Balder","Norse","...",""} });

	auto* greek_gods = new Link{ God{"Hera","Greek","..."} };

	greek_gods = greek_gods->add(new Link{ God{ "Hestia","Greek","..." } });
	greek_gods = greek_gods->add(new Link{ God{ "Demeter","Greek","..." } });
	greek_gods = greek_gods->add(new Link{ God{ "Ares","Greek","..." } });

	auto* egyptian_gods = new Link{ God{"Set","Egypt","..."} };

	egyptian_gods = egyptian_gods->add(new Link{ God{ "Ra","Egypt","..." } });
	egyptian_gods = egyptian_gods->insert(new Link{ God{"Isis","Egypt","...",""} });

	if (const auto* found{ greek_gods->find("Hestia") }; found)
	{
		std::cout << "Found\n\n";
	}

	print_all(norse_gods);
	std::cout << "\n\n";

	print_all(greek_gods);
	std::cout << "\n\n";

	print_all(egyptian_gods);
	std::cout << "\n\n";
}