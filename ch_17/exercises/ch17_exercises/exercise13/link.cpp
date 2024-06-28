#include "link.h"
#include <iostream>

Link* Link::insert(Link* n)
{
	if (!n)
	{
		return this;
	}

	if (!this)
	{
		return n;
	}

	n->succ = this;

	if (prev)
	{
		prev->succ = n;
	}

	n->prev = prev;

	prev = n;

	return n;
}

Link* Link::add(Link* n)
{
	if (!n)
	{
		return this;
	}

	if (!this)
	{
		return n;
	}

	n->prev = this;

	if (succ)
	{
		succ->prev = n;
	}

	n->succ = succ;

	succ = n;

	return n;
}

Link* Link::add_ordered(Link* n)
{
	if (!n)
	{
		return this;
	}

	if (!this)
	{
		return n;
	}

	auto* p1{ first_index() };

	while (p1->succ)
	{
		if (n->god.name <= p1->god.name) {
			return p1->insert(n);
		}

		if (n->god.name <= p1->succ->god.name)
		{
			return p1->add(n);
		}

		p1 = p1->advance(p1, 2);
	}

	return p1->add(n);
}

Link* Link::erase(Link* p)
{
	if (!p) {
		return nullptr;
	}

	if (p->succ)
	{
		p->succ->prev = p->prev;
	}

	if (p->prev)
	{
		p->prev->succ = p->succ;
	}

	return p->succ;
}

Link* Link::find(std::string_view s)
{
	auto* p1 = first_index();

	while (p1)
	{
		if (p1->god.name == s)
		{
			return p1;
		}

		p1 = p1->succ;
	}

	return nullptr;
}

const Link* Link::find(std::string_view s) const
{
	return const_cast<Link*>(this)->find(s);
}

Link* Link::first_index()
{
	auto* p1{ this };

	while (p1->prev)
	{
		p1 = p1->advance(p1, -1);
	}

	return p1;
}

Link* Link::advance(Link* p, int n) const
{
	if (!p)
	{
		return nullptr;
	}

	if (n > 0)
	{
		while (n--)
		{
			if (!p->succ)
			{
				return nullptr;
			}

			p = p->succ;
		}
	}

	else if (n < 0)
	{
		while (n++)
		{
			if (!p->prev)
			{
				return nullptr;
			}

			p = p->prev;
		}
	}

	return p;
}

void print_all(const Link* p)
{
	std::cout << "{ \n";

	while (p)
	{
		p->value().print_all();
		std::cout << "\n";
		p = p->next();
	}

	std::cout << "\n}";
}