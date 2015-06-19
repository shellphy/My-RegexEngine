#include "DFA.h"
#include "NFA.h"
#include <deque>
#include <unordered_map>
#include <iostream>

DFA::DFA(string str) : nfa(str)
{
	head = nullptr;
	nodeNumber = 0;
	alphabeta.clear();
	nodes.clear();
	edges.clear();

	NFA_to_DFA();
//	print();
}

void DFA::operator=(string str)
{
	delete head;
	nfa = str;
	head = nullptr;
	nodeNumber = 0;
	alphabeta.clear();
	nodes.clear();
	edges.clear();

	NFA_to_DFA();
//	print();
}

DFA::~DFA()
{
	delete head;
}

void DFA::print()
{
	cout << "\nDFA::" << endl;
	DFA_Node *node = head;
	while (node != nullptr)
	{
		DFA_Edge *edge = node->edges;
		while (edge != nullptr)
		{
			cout << "\t" << edge->from->num << " ---- (" << edge->c << ") ---- " << edge->to->num << endl;
			edge = edge->next;
		}
		if (node->isAccept == true)
			cout << node->num << " is accept" << endl;
		else
			cout << node->num << " is not accept" << endl;
		node = node->next;
	}
}

set<int> DFA::delta(set<int> *q, char c)
{
	set<int> node;
	for (auto pos = nfa.getEdges().equal_range(c); pos.first != pos.second; ++pos.first)
	{
		if (q->find(pos.first->second->from->num) != q->end())
			node.insert(pos.first->second->to->num);
	}
	return node;
}

set<int> DFA::eps_closure(set<int> x)
{
	set<int> eps_closure;
	deque<int> Q;
	for (auto it = x.begin(); it != x.end(); ++it)
	{
		Q.push_back(*it);
		while (!Q.empty())
		{
			auto q = Q.front();
			Q.pop_front();
			eps_closure.insert(q);
			auto test = nfa.getNodes()[q];
			for (auto p = (nfa.getNodes())[q]->edges; p != nullptr && p->ch == EPS; p = p->next)
			{
				if (p->to->visit == false)
				{
					Q.push_back(p->to->num);
					p->to->visit = true;
				}
			}
		}
	}
	nfa.resetNodesVisit();
	return eps_closure;
}

void DFA::subsetConstruct()
{
	int num = 0;
	auto q0 = eps_closure({ nfa.getStart() });
	deque<set<int>> worklist;
	worklist.push_back(q0);
	while (!worklist.empty())
	{
		auto q = new set<int>(worklist.front());
		worklist.pop_front();
		for (auto c = alphabeta.begin(); c != alphabeta.end(); ++c)
		{
			set<int> v = delta(q, *c);
			if (v.size() == 0)
				continue;
			auto t = new set<int>(eps_closure(v));
			addEdge(q, t, *c);
			if (needNewNode == true)
			{
				worklist.push_back(*t);
				needNewNode = false;
			}
		}
	}
}

DFA_Node *DFA::loopUpOrInsert(set<int> *s)
{
	DFA_Node *node = head;
	while (node != nullptr)
	{
		if (*(node->q) == *s)
			return node;
		node = node->next;
	}
	DFA_Node *p = new DFA_Node(nodeNumber++, s, nullptr, nullptr, false);
	if (s->find(nfa.getAccept()) != s->end())
		p->isAccept = true;
	needNewNode = true;
	p->next = head;
	head = p;
	return p;
}

void DFA::addEdge(set<int> *from, set<int> *to, char c)
{
	DFA_Node *f = loopUpOrInsert(from);
	DFA_Node *t = loopUpOrInsert(to);
	DFA_Edge *edge = new DFA_Edge(c, f, t, f->edges);
	f->edges = edge;
}

void DFA::NFA_to_DFA()
{
	for (auto it = nfa.getEdges().cbegin(); it != nfa.getEdges().cend(); ++it)
		alphabeta.insert(it->first);
	subsetConstruct();
	newNodesAndEdges();
}

void DFA::newNodesAndEdges()
{
	nodes.resize(nodeNumber);
	for (DFA_Node *p = head; p != nullptr; p = p->next)
	{
		nodes[p->num] = p;
		for (DFA_Edge *q = p->edges; q != nullptr; q = q->next)
		{
			edges.insert({ q->c, q });
		}
	}
}

vector<DFA_Node *> &DFA::getNodes()
{
	return nodes;
}

multimap<char, DFA_Edge *> &DFA::getEdges()
{
	return edges;
}

DFA_Node *DFA::getHead()
{
	return head;
}

set<char> DFA::getAlphabeta()
{
	return alphabeta;
}
