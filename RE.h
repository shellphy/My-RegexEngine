#ifndef _RE_H
#define _RE_H

#include "RE_Tree.h"
#include "NFA.h"
#include "DFA.h"
#include "MDFA.h"
#include <string>
#include <vector>

using namespace std;

class RE
{
private:
	MDFA mdfa;
	string test_str;
	int pos;
	char currentChar;
	vector<MDFA_Node *> nodes;
	bool isMatched;
	string matchedString;
	char getNextChar();
	void rollBack();
public:
	RE(string exp = "");
	void replace(string s);
	bool match(string test_str);
	bool search(string test_str, vector<string> &result);
};

#endif