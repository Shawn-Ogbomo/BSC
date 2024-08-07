#ifndef LINK_H
#define LINK_H
#include <string>

class Link {
public:
	Link(const std::string& v, Link* p = nullptr, Link* s = nullptr)
		: prev{ p }, succ{ s }, value{ v } { }
	// INSERT N BEFORE THIS OBJECT
	Link* insert(Link* n);
	// INSERT N AFTER THIS OBJECT
	Link* add(Link* n);
	// REMOVE THIS OBJECT FROM LIST
	Link* erase(Link* p);
	// FIND S IN LIST
	Link* find(const std::string& s);
	// FIND S IN CONST LIST (SEE �18.5.1)
	const Link* find(const std::string& s) const;
	// MOVE N POSITIONS IN LIST
	Link* advance(Link* p, int n) const;
	Link* next() const { return succ; }
	Link* previous() const { return prev; }
	std::string val() const { return value; };
private:
	Link* prev;
	Link* succ;
	std::string value;
};

void print_all(const Link* p);

#endif // !LINK_H