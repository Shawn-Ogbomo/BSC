#ifndef LINK_H
#define LINK_H

#include <string>

class Link {
public:
	Link(std::string_view v, Link* s = nullptr)
		: val{ v }, succ{ s } { }
	~Link();
	// INSERT N AFTER THIS OBJECT
	Link* add(Link* n);
	// REMOVE THIS OBJECT FROM LIST
	//Link* erase();
	Link* insert(Link* h, Link* n);
	Link* find(std::string_view s);
	const Link* find(std::string_view s) const;
	Link* advance(int n) const;
	Link* next() const { return succ; };
	std::string_view value() const { return val; };
private:
	std::string val;
	Link* succ;
};

void print_all(const Link* p);

#endif // !LINK_H