#ifndef _DFA_EDGE_H
#define _DFA_EDGE_H

class DFA_Node;

class DFA_Edge
{
public:
	char c;
	DFA_Node *from, *to;
	DFA_Edge *next;

	DFA_Edge(char c, DFA_Node *from, DFA_Node *to, DFA_Edge *next)
	{
		this->c = c;
		this->from = from;
		this->to = to;
		this->next = next;
	}
};


#endif