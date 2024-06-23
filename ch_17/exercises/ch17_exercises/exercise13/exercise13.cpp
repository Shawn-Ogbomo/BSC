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

int main() {
	auto* norse_gods = new Link{ God{"Zeus","Greek","Lightning",""} };

	//norse_gods = norse_gods->insert(new Link{ God{"","","",""} });
	//norse_gods = norse_gods->insert(new Link{ "Zeus" });
	//norse_gods = norse_gods->insert(new Link{ "Freia" });

	//auto* greek_gods = new Link{ "Hera" };
	//greek_gods = greek_gods->insert(new Link{ "Athena" });
	//greek_gods = greek_gods->insert(new Link{ "Mars" });
	//greek_gods = greek_gods->insert(new Link{ "Poseidon" });

	print_all(norse_gods);

	//std::cout << "\n";

	//print_all(greek_gods);
}