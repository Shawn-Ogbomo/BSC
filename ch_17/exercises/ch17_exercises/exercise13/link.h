#ifndef LINK_H
#define LINK_H

#include <string>
#include "god.h"

class Link {
public:
	Link(const God& g, Link* p = nullptr, Link* s = nullptr)
		: god{ g }, prev{ p }, succ{ s } { }
	// INSERT N BEFORE THIS OBJECT
	Link* insert(Link* n);
	// INSERT N AFTER THIS OBJECT
	Link* add(Link* n);
	// INSERTS NEW ELEMENT IN ITS CORRECT LEXICOGRAPHICAL POSITION
	Link* add_ordered(Link* n);
	// REMOVE THIS OBJECT FROM LIST
	Link* erase(Link* p);
	Link* find(std::string_view s);
	const Link* find(std::string_view s) const;
	Link* first_index();
	Link* advance(Link* p, int n) const;
	Link* next() const { return succ; };
	Link* previous() const { return prev; };
	const God& value() const { return god; };
private:
	God god;
	Link* prev;
	Link* succ;
};

void print_all(const Link* p);

#endif // !LINK_H