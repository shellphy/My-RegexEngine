#ifndef _RE_TREENODE_H
#define _RE_TREENODE_H

// 正则表达式树的节点的类型
enum NodeKind {
	Element,	// 字符
	ALT,		// 选择运算
	CONCAT,		// 连接运算
	CLOSURE		// 闭包运算
};

class RE_TreeNode
{
public:
	NodeKind nodeKind;
	char ch;
	RE_TreeNode *child[2];		// 每个节点最多两个孩子

	RE_TreeNode(NodeKind nodeKind, char ch, RE_TreeNode *child0, RE_TreeNode *child1)
	{
		this->nodeKind = nodeKind;
		this->ch = ch;
		child[0] = child0;
		child[1] = child1;
	}
};

#endif