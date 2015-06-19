#ifndef _DFA_H
#define _DFA_H

#include "DFA_Node.h"
#include "DFA_Edge.h"
#include "NFA.h"
#include <set>
#include <map>
#include <vector>

using namespace std;

class DFA
{
private:
	/* NFA的实例 */
	NFA nfa;

	/* 顶点的个数 */
	int nodeNumber;

	/* 字母表, 存储当前正则表达式中的所有字符 */
	set<char> alphabeta;

	/* 邻接表的头指针 */
	DFA_Node *head;

	/* 把所有的顶点存储为一个数组, 因为每个顶点都有一个唯一的标识符num, 用num来索引顶点指针 */
	vector<DFA_Node *> nodes;

	/* 把所有边存储为一个multimap, 根据边上的字符来索引边的指针 */
	multimap<char, DFA_Edge *> edges;

	/* 在子集构造算法中判断是否需要新建一个顶点 */
	bool needNewNode;

	/*
	在邻接表中查找有没有与集合s相同的集合的顶点, 如果有,则返回指向该节点的指针
	否则创建一个新的节点并返回指向该节点的指针
	*/
	DFA_Node *loopUpOrInsert(set<int> *s);

	/* 新建一条边 */
	void addEdge(set<int> *from, set<int> *to, char c);

	/* 从顶点集合q中通过字符q可以转移到的顶点的集合 */
	set<int> delta(set<int> *q, char c);

	/* 顶点集合x不需要通过任何字符就可以转移到的顶点的集合 */
	set<int> eps_closure(set<int> x);

	/* 子集构造算法 */
	void subsetConstruct();

	/* 创建nodes和edges数组 */
	void newNodesAndEdges();

public:
	DFA(string str);
	void operator=(string str);
	~DFA();

	/* 驱动从NFA到DFA的转换 */
	void NFA_to_DFA();

	/* 返回字母表 */
	set<char> getAlphabeta();

	/* 返回邻接链表的头指针 */
	DFA_Node *getHead();

	/* 返回顶点数组 */
	vector<DFA_Node *> &getNodes();

	/* 返回边数组 */
	multimap<char, DFA_Edge *> &getEdges();

	/* 打印结果, 测试 */
	void print();
};

#endif