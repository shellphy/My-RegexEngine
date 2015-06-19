#include "RE_Tree.h"
#include <iostream>
#include <string>

using namespace std;

RE_Tree::RE_Tree(string str)
{
	exp = str;
	pos = 0;
	currentChar = '\0';
	root = nullptr;

	toRE_Tree();
//	print();
}

void RE_Tree::operator=(string str)
{
	delete root;
	exp = str;
	pos = 0;
	currentChar = '\0';
	root = nullptr;

	toRE_Tree();
//	print();
}

RE_Tree::~RE_Tree()
{
	delete root;
}

void RE_Tree::toRE_Tree()
{
	currentChar = getNextChar();
	if (currentChar == '\0')
		return;
	root = parse_exp();
}

void RE_Tree::print()
{
	cout << "正则表达式树为: " << endl;
	printTree(root);
}

char RE_Tree::getNextChar()
{
	return exp[pos++];
}

RE_TreeNode * RE_Tree::parse_exp()
{
	RE_TreeNode *t = parse_A();
	while (currentChar == '|')
	{
		currentChar = getNextChar();
		RE_TreeNode *p = parse_A();
		RE_TreeNode *alt = new RE_TreeNode(ALT, '|', t, p);
		t = alt;
	}
	return t;
}

RE_TreeNode * RE_Tree::parse_A()
{
	RE_TreeNode *t = parse_B();
	if (currentChar == '\0')
		return t;
	while (currentChar == '(' || isalpha(currentChar))
	{
		RE_TreeNode *p = parse_B();
		RE_TreeNode *add = new RE_TreeNode(CONCAT, '+', t, p);
		t = add;
	}
	return t;
}

RE_TreeNode * RE_Tree::parse_B()
{
	RE_TreeNode *t = parse_C();
	if (currentChar == '\0')
		return t;
	while (currentChar == '*')
	{
		currentChar = getNextChar();
		RE_TreeNode *kleene = new RE_TreeNode(CLOSURE, '*', t, nullptr);
		t = kleene;
	}
	return t;
}

RE_TreeNode * RE_Tree::parse_C()
{
	RE_TreeNode *t = nullptr;
	if (currentChar == '(')
	{
		currentChar = getNextChar();
		t = parse_exp();
		currentChar = getNextChar();
	}
	else
	{
		t = new RE_TreeNode(Element, currentChar, nullptr, nullptr);
		currentChar = getNextChar();
	}
	return t;
}

RE_TreeNode *RE_Tree::getTreeRoot()
{
	return root;
}

void RE_Tree::printTree(RE_TreeNode *tree)
{
	static int indentno = 0;
	indentno += 2;
	if (tree != nullptr)
	{
		for (int i = 0; i < indentno; i++)
			cout << " ";
		cout << tree->ch << endl;
		printTree(tree->child[0]);
		printTree(tree->child[1]);
	}
	indentno -= 2;
}
