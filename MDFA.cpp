#include "MDFA.h"
#include "DFA.h"
#include "MDFA_Edge.h"
#include "MDFA_Node.h"
#include <deque>
#include <iostream>
#include <set>

using namespace std;

MDFA::MDFA(string str) : dfa(str)
{
	nodeNumber = 0;
	head = nullptr;
	nodes.clear();
	alphabeta.clear();
	T.clear();
	P.clear();

	minimizeDFA();
//	print();
}

void MDFA::operator=(string str)
{
	delete head;
	dfa = str;
	nodeNumber = 0;
	head = nullptr;
	nodes.clear();
	alphabeta.clear();
	T.clear();
	P.clear();

	minimizeDFA();
//	print();
}

MDFA::~MDFA()
{
	delete head;
}

void MDFA::hopcroft()
{
	set<int> accept, notaccepet;
	for (auto node = dfa.getHead(); node != nullptr; node = node->next)
	{
		if (node->isAccept == true)
			accept.insert(node->num);
		else
			notaccepet.insert(node->num);
	}
	T.insert(accept);
	T.insert(notaccepet);
	while (P != T)
	{
		P = T;
		T.clear();
		for (auto it = P.begin(); it != P.end(); ++it)
		{
			auto temp = *it;
			auto first = split(temp).first;
			if (!first.empty())
				T.insert(first);

			auto second = split(temp).second;
			if (!second.empty())
				T.insert(second);
		}
	}
}

pair<set<int>, set<int>> MDFA::split(set<int> S)
{
	set<int> temp = S;
	set<int> s1, s2;
	for (auto c = alphabeta.begin(); c != alphabeta.end(); ++c)
	{
		for (auto pos = dfa.getEdges().equal_range(*c); pos.first != pos.second && S.find(pos.first->second->from->num) != S.end(); ++pos.first)
		{
			bool bl = false;
			set<set<int>> ::iterator firstSet = P.begin();
			for (set<set<int>>::iterator it = P.begin(); it != P.end(); ++it)
			{
				int from = pos.first->second->from->num;
				int to = pos.first->second->to->num;
				if (it->find(to) != it->end() && *it != temp)
				{
					if (bl == false)
					{
						firstSet = it;
						s1.insert(from);
						S.erase(from);
						bl = true;
					}
					else
					{
						if (firstSet == it)
						{
							s1.insert(from);
							S.erase(from);
						}
						else
						{
							s2.insert(from);
							S.erase(from);
						}
					}
				}
				else if (it->find(to) != it->end() && *it == temp)
				{
					s2.insert(from);
					S.erase(from);
				}
			}

		}
		if (temp != S)
		{
			if (!s1.empty())
			{
				s2.insert(S.begin(), S.end());
				return make_pair(s1, s2);
			}
			else
			{
				return make_pair(s2, S);
			}
		}
	}
	return make_pair(S, S);
}

void MDFA::minimizeDFA()
{
	for (auto it = dfa.getEdges().begin(); it != dfa.getEdges().end(); ++it)
		alphabeta.insert((*it).first);
	hopcroft();

	// 先创建节点
	for (auto it = T.begin(); it != T.end(); ++it)
	{
		auto node = new set<int>(*it);
		auto p = new MDFA_Node(nodeNumber++, node, false, nullptr, head);
		head = p;
		for (auto s = it->begin(); s != it->end(); ++s)
		{
			if (dfa.getNodes()[*s]->isAccept == true)
				p->isAccept = true;
		}
	}

	nodes.resize(nodeNumber);
	for (auto p = head; p != nullptr; p = p->next)
		nodes[p->num] = p;

	// 再创建边
	for (auto p = dfa.getHead(); p != nullptr; p = p->next)
	{
		for (auto q = p->edges; q != nullptr; q = q->next)
		{
			addEdge(q->from->num, q->to->num, q->c);
		}
	}
}

void MDFA::addEdge(int f, int t, char c)
{
	int from = findNode(f);
	int to = findNode(t);
	auto it = nodes[from]->edges;
	while (it != nullptr)
	{
		if (it->c == c)
			return;
		it = it->next;
	}
	auto p = new MDFA_Edge(c, nodes[from], nodes[to], nodes[from]->edges);
	nodes[from]->edges = p;
}

int MDFA::findNode(int n)
{
	for (int i = 0; i < nodeNumber; i++)
	{
		if (nodes[i]->s->find(n) != nodes[i]->s->end())
		{
			return i;
		}
	}
}

vector<MDFA_Node *> & MDFA::getNodes()
{
	return nodes;
}

void MDFA::print()
{
	cout << "\nMDFA::" << endl;
	MDFA_Node *node = head;
	while (node != nullptr)
	{
		MDFA_Edge *edge = node->edges;
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
