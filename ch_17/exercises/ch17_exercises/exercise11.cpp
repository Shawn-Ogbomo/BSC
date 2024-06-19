//Complete the “list of gods” example from §17.10.1 and run it.
#include <iostream>
#include "link.h"

int main() {
	auto* norse_gods = new Link{ "Thor" };

	norse_gods = norse_gods->insert(new Link{ "Odin" });
	norse_gods = norse_gods->insert(new Link{ "Zeus" });
	norse_gods = norse_gods->insert(new Link{ "Freia" });

	auto* greek_gods = new Link{ "Hera" };

	greek_gods = greek_gods->insert(new Link{ "Athena" });
	greek_gods = greek_gods->insert(new Link{ "Mars" });
	greek_gods = greek_gods->insert(new Link{ "Poseidon" });

	greek_gods = greek_gods->add(new Link{ "Demeter" });
	greek_gods = greek_gods->insert(new Link{ "Hestia" });

	if (const auto* found = greek_gods->find("Athena"); found) {
		std::cout << "found: " << found->value;
	}

	const auto* p1{ greek_gods };

	while (p1) {
		std::cout << p1->value << "\n";
		p1 = p1->next();
	}
}