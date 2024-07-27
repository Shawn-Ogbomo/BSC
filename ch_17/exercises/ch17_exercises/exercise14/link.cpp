#include "link.h"
#include <iostream>

//Link::~Link()
//{
//	auto* p1{ this };
//
//	while (p1)
//	{
//		p1 = p1->erase();
//	}
//}

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

	auto* next{ succ };

	succ = n;
	n->succ = next;

	return this;
}

//Link* Link::erase()
//{
//	if (!this)
//	{
//		return nullptr;
//	}
//
//	auto* p{ this };
//
//	while (p != this)
//	{
//		if (h->succ == this)
//		{
//			h->succ = h->succ->succ;
//			p->succ = nullptr;
//			return h;
//		}
//
//		h = h->succ;
//	}
//
//	return h->succ;
//}

Link* Link::insert(Link* h, Link* n)
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

	while (h != this)
	{
		if (h->succ == this)
		{
			h->succ = n;
			return h;
		}

		h = h->succ;
	}

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

Link* Link::advance(int n) const
{
	if (!this)
	{
		return nullptr;
	}

	auto* p{ this };

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

	return const_cast<Link*>(p);
}

void print_all(const Link* p)
{
	while (p)
	{
		std::cout << p->value() << "\n";
		p = p->next();
	}
}