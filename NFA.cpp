#include "NFA.h"
#include <iostream>

using namespace std;

NFA::NFA(string str) : reTree(str)
{
	nodeNumber = 0;
	head = nullptr;
	start = accept = 0;
	nodes.clear();
	edges.clear();

	RE_to_NFA();
//	print();
}

void NFA::operator=(string str)
{
	delete head;
	reTree = str;
	nodeNumber = 0;
	head = nullptr;
	start = accept = 0;
	nodes.clear();
	edges.clear();

	RE_to_NFA();
//	print();
}

NFA::~NFA()
{
	delete head;
}

int NFA::getStart()
{
	return start;
}

int NFA::getAccept()
{
	return accept;
}

void NFA::RE_to_NFA()
{
	Thompson(reTree.getTreeRoot());
	newNodesAndEdges();
}

void NFA::newNodesAndEdges()
{
	nodes.resize(nodeNumber);
	for (NFA_Node *p = head; p != nullptr; p = p->next)
	{
		nodes[p->num] = p;
		for (NFA_Edge *q = p->edges; q != nullptr && q->ch != EPS; q = q->next)
		{
			edges.insert({ q->ch, q });
		}
	}
}

vector<NFA_Node *> &NFA::getNodes()
{
	return nodes;
}

multimap<char, NFA_Edge *> &NFA::getEdges()
{
	return edges;
}

void NFA::resetNodesVisit()
{
	auto p = head;
	while (p != nullptr)
	{
		p->visit = false;
		p = p->next;
	}
}

NFA_Node* NFA::loopUpOrInsert(int num)
{
	NFA_Node *node = head;
	while (node != nullptr)
	{
		if (node->num == num)
			return node;
		node = node->next;
	}
	NFA_Node *p = new NFA_Node(num);
	p->next = head;
	head = p;
	return p;
}

void NFA::addEdge(int from, int to, char ch)
{
	NFA_Node *f = loopUpOrInsert(from);
	NFA_Node *t = loopUpOrInsert(to);
	NFA_Edge *edge = new NFA_Edge(ch, f, t, f->edges);
	f->edges = edge;
}

void NFA::Thompson(RE_TreeNode *e)
{
	if (e->nodeKind == Element)
	{
		int from = nodeNumber++;
		int to = nodeNumber++;
		addEdge(from, to, e->ch);
		start = from;
		accept = to;
	}
	else if (e->nodeKind == ALT)
	{
		Thompson(e->child[0]);
		int start1 = start;
		int accept1 = accept;
		Thompson(e->child[1]);
		int start2 = start;
		int accept2 = accept;
		int from = nodeNumber++;
		addEdge(from, start1, EPS);
		addEdge(from, start2, EPS);
		int to = nodeNumber++;
		addEdge(accept1, to, EPS);
		addEdge(accept2, to, EPS);
		start = from;
		accept = to;
	}
	else if (e->nodeKind == CONCAT)
	{
		Thompson(e->child[0]);
		int oldStart = start;
		int oldAccept = accept;
		Thompson(e->child[1]);
		addEdge(oldAccept, start, EPS);
		start = oldStart;
	}
	else if (e->nodeKind == CLOSURE)
	{
		Thompson(e->child[0]);
		addEdge(accept, start, EPS);
		int from = nodeNumber++;
		addEdge(from, start, EPS);
		int to = nodeNumber++;
		addEdge(from, to, EPS);
		addEdge(accept, to, EPS);
		start = from;
		accept = to;
	}
}

void NFA::print()
{
	cout << "\nNFA: " << endl;
	NFA_Node *node = head;
	while (node)
	{
		NFA_Edge *edge = node->edges;
		while (edge)
		{
			if (edge->ch == -2)
				cout << "\t" << edge->from->num << " --- (ESP) ---- " << edge->to->num << endl;
			else
				cout << "\t" << edge->from->num << " ---- (" << edge->ch << ") ---- " << edge->to->num << endl;
			edge = edge->next;
		}
		node = node->next;
	}
}
