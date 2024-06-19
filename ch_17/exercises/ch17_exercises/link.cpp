#include "link.h"

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

	prev = n;

	return n;
}

Link* Link::add(Link* n)
{
}

Link* Link::erase()
{
}

Link* Link::find(const std::string& s)
{
	auto* p1 = this;

	while (p1)
	{
		if (p1->value == s)
		{
			return p1;
		}

		p1 = p1->succ;
	}

	return nullptr;
}

const Link* Link::find(const std::string& s) const
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

	if (n < 0)
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