#ifndef _MDFA_H
#define _MDFA_H

#include "DFA.h"
#include "MDFA_Node.h"
#include "MDFA_Edge.h"

class MDFA
{
private:
	/* DFA的实例 */
	DFA dfa;

	/* 顶点的个数 */
	int nodeNumber;

	/* 邻接表的头指针 */
	MDFA_Node *head;

	/* 把所有的顶点存储为一个数组, 因为每个顶点都有一个唯一的标识符num, 用num来索引顶点指针 */
	vector<MDFA_Node *>nodes;

	/* 字母表, 存储当前正则表达式中的所有字符 */
	set<char> alphabeta;

	/* 在Hopcroft算法中,需要用来判断两次划分有没有变化, P用来保存前一次划分的结果, T用来保存划分后的结果 */
	set<set<int>> T, P;

	/* 划分算法 */
	pair<set<int>, set<int>> split(set<int> S);

	/* Hopcroft算法 */
	void hopcroft();

	/* 新建一条边 */
	void addEdge(int f, int t, char c);

	/* 给定DFA中顶点的标识数, 返回该顶点在MDFA中的标识数 */
	int findNode(int i);

public:
	MDFA(string str);
	void operator=(string str);
	~MDFA();

	/* 最小化DFA */
	void minimizeDFA();

	vector<MDFA_Node *> &getNodes();

	/* 打印结果, 测试 */
	void print();
};

#endif
