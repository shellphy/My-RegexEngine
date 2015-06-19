#ifndef _NFA_H
#define _NFA_H

#include "NFA_Node.h"
#include "NFA_Edge.h"
#include "RE_TreeNode.h"
#include "RE_Tree.h"
#include <vector>
#include <map>

using namespace std;

class NFA
{
private:
	/* 正则表达式树的实例 */
	RE_Tree reTree;

	/* 指向邻接表的头指针 */
	NFA_Node *head;

	/* 顶点数 */
	int nodeNumber;

	/* 开始状态和接收状态 */
	int start, accept;

	/* 把所有的顶点存储为一个数组, 因为每个顶点都有一个唯一的标识符num, 用num来索引顶点指针 */
	vector<NFA_Node *> nodes;

	/* 把所有非EPS边存储为一个multimap, 根据边上的字符来索引边的指针 */
	multimap<char, NFA_Edge *> edges;

	/* 创建nodes和edges数组 */
	void newNodesAndEdges();

	/* Thompson算法 */
	void Thompson(RE_TreeNode *tree);

	/* 添加一条边 */
	void addEdge(int from, int to, char ch);

	/*
	在邻接表中查找有没有num标识的顶点, 如果有,则返回指向该顶点的指针,
	否则创建一个新的顶点并返回指向该顶点的指针
	*/
	NFA_Node* loopUpOrInsert(int num);

public:
	NFA(string str);
	void operator=(string str);
	~NFA();

	/* 返回开始顶点的标识 */
	int getStart();

	/* 返回接收状态顶点的标识 */
	int getAccept();

	/* 驱动从正则表达式到NFA的转换 */
	void RE_to_NFA();

	/* 设置所有的节点的访问状态为false */
	void resetNodesVisit();

	/* 返回顶点数组 */
	vector<NFA_Node *> &getNodes();

	/* 返回边数组 */
	multimap<char, NFA_Edge *> &getEdges();

	// 测试
	void print();
};

#endif