#ifndef _NFA_EDGE_H
#define _NFA_EDGE_H

#include "NFA_Node.h"

const char EPS = -2;

class NFA_Node;

class NFA_Edge
{
public:
	signed char ch;
	NFA_Node *from;
	NFA_Node *to;
	NFA_Edge *next;

	NFA_Edge(char ch, NFA_Node *from, NFA_Node *to, NFA_Edge *next)
	{
		this->from = from;
		this->to = to;
		this->next = next;
		this->ch = ch;
	}
};

#endif