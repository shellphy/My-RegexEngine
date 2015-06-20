#ifndef _RE_TREE_H
#define _RE_TREE_H

#include "RE_TreeNode.h"
#include <string>
#include <set>

using namespace std;

class RE_Tree
{
private:
	/* exp用来存储正则表达式 */
	string exp;

	/* pos是指向exp的位置指针 */
	int pos;

	/* 保存当前的字符 */
	char currentChar;

	/* reTree是指向正则表达式树的根节点 */
	RE_TreeNode *root;

	/* 遍历exp时, 返回exp中的下一个字符 */
	char getNextChar();

	/*
	正则表达式的BNF
	    exp -> exp | A
	        -> A
	      A -> A + B
	        -> B
	      B -> C*
	        -> C
	      C -> ( exp )
	        -> e
	用递归下降的方式来解析正则表达式, 生成表达式树
	下面的四个函数分别对应于BNF中的四个推导
	*/
	RE_TreeNode *parse_exp();
	RE_TreeNode *parse_A();
	RE_TreeNode *parse_B();
	RE_TreeNode *parse_C();

public:
	RE_Tree(string str);
	void operator=(string str);
	~RE_Tree();

	/* 返回表达式树的根节点指针 */
	RE_TreeNode *getTreeRoot();

	/* 根据表达式exp来生成表达式树 */
	void toRE_Tree();

	// 测试
	void print();
	void printTree(RE_TreeNode *reTree);
};

#endif 
