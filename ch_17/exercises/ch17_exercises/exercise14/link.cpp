#include "link.h"
#include <iostream>

Link::~Link()
{
	auto* p1{ this };

	while (p1)
	{
		p1 = p1->erase(p1);
	}
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

	if (!succ)
	{
		succ = n;
		return n;
	}

	auto* next{ succ };

	succ = n;
	n->succ = next;

	return n;
}

Link* Link::erase(Link* p)
{
	if (!this)
	{
		return nullptr;
	}

	if (!p)
	{
		return this;
	}

	if (!succ)
	{
		while (p->succ)
		{
			if (!p->succ->succ)
			{
				p->succ = nullptr;
				return p;
			}

			p = p->succ;
		}

		return p->succ;
	}

	while (p != this)
	{
		if (p->succ == this)
		{
			p->succ = p->succ->succ;
			succ = nullptr;
			return p;
		}

		p = p->succ;
	}

	return p->succ;
}

Link* Link::insert(Link* n)
{
	if (!this)
	{
		return n;
	}

	if (!n)
	{
		return this;
	}

	n->succ = this;

	// get the link before this and point to n

	return n;
}

Link* Link::find(std::string_view s)
{
	auto* p1{ this };

	while (p1)
	{
		if (p1->val == s)
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

	return p;
}

void print_all(const Link* p)
{
	while (p)
	{
		std::cout << p->value() << "\n";
		p = p->next();
	}
}