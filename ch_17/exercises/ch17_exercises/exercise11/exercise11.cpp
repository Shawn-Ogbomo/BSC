//Complete the “list of gods” example from §17.10.1 and run it.
#include <iostream>
#include "link.h"

int main() {
	auto* norse_gods = new Link{ "Thor",nullptr,new Link{"Shawn"} };

	norse_gods = norse_gods->add(new Link{ "Odin" });
	norse_gods = norse_gods->insert(new Link{ "Zeus" });
	norse_gods = norse_gods->insert(new Link{ "Freia" });

	std::cout << norse_gods->advance(norse_gods, 2)->val();

	auto* greek_gods = new Link{ "Hera" };

	greek_gods = greek_gods->insert(new Link{ "Athena" });
	greek_gods = greek_gods->insert(new Link{ "Mars" });
	greek_gods = greek_gods->insert(new Link{ "Poseidon" });

	greek_gods = greek_gods->add(new Link{ "Demeter" });
	greek_gods = greek_gods->insert(new Link{ "Hestia" });

	if (const auto* found = greek_gods->find("Athena"); found) {
		std::cout << "found: " << found->val();
	}

	const auto* p1{ greek_gods };

	while (p1) {
		std::cout << p1->val() << "\n";
		p1 = p1->next();
	}
}