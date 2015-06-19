#ifndef _MDFA_NODE_H
#define _MDFA_NODE_H

#include "MDFA_Edge.h"
#include <set>

using namespace std;

class MDFA_Node
{
public:
	int num;
	set<int> *s;	// s指向DFA中的顶点的集合
	bool isAccept;
	MDFA_Edge *edges;
	MDFA_Node *next;
	MDFA_Node(int num, set<int> *s, bool isAccept, MDFA_Edge *edge, MDFA_Node *next)
	{
		this->num = num;
		this->s = s;
		this->isAccept = isAccept;
		this->edges = edge;
		this->next = next;
	}
};

#endif