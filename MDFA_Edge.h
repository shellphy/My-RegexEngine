#ifndef _MDFA_EDGE_H
#define _MDFA_EDGE_H

#include "MDFA_Node.h"

class MDFA_Node;

class MDFA_Edge
{
public:
	char c;
	MDFA_Node *from, *to;
	MDFA_Edge *next;
	MDFA_Edge(char c, MDFA_Node *from, MDFA_Node *to, MDFA_Edge *next)
	{
		this->c = c;
		this->from = from;
		this->to = to;
		this->next = next;
	}
};

#endif