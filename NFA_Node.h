#ifndef _NFA_NODE_H
#define _NFA_NODE_H

#include "NFA_Edge.h"

class NFA_Node
{
public:
	int num;
	bool visit;
	NFA_Node *next;
	NFA_Edge *edges;

	NFA_Node(int n = 0)
	{
		num = n;
		visit = false;
		next = nullptr;
		edges = nullptr;
	}
};

#endif
