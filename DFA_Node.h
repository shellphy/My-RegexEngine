#ifndef _DFA_NODE_H
#define _DFA_NODE_H

#include "DFA_Edge.h"
#include <set>

using namespace std;

class DFA_Node
{
public:
	int num;
	set<int> *q;	// 节点指向NFA中的状态集合
	bool isAccept;
	DFA_Edge *edges;
	DFA_Node *next;

	DFA_Node(int num, set<int> *q, DFA_Edge *edges, DFA_Node *next, bool isAccept)
	{
		this->num = num;
		this->q = q;
		this->edges = edges;
		this->next = next;
		this->isAccept = isAccept;
	}
};

#endif