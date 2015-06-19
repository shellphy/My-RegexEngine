#include "RE.h"
#include <string>
#include <deque>

using namespace std;

RE::RE(string exp) : mdfa(exp)
{
	pos = 0;
	nodes = mdfa.getNodes();
}

void RE::replace(string exp)
{
	pos = 0;
	mdfa = exp;
	nodes = mdfa.getNodes();
}

char RE::getNextChar()
{
	return test_str[pos++];
}

void RE::rollBack()
{
	pos--;
}

bool RE::match(string test_str)
{
	pos = 0;
	this->test_str = test_str;
	currentChar = getNextChar();
	bool isMatched;
	int state = 0;
	MDFA_Edge *edge = nullptr;

s:
	if (nodes[state]->isAccept == true && currentChar == '\0')
	{
		isMatched = true;
		goto out;
	}
	edge = nodes[state]->edges;
	while (edge != nullptr)
	{
		if (edge->c == currentChar)
		{
			currentChar = getNextChar();
			state = edge->to->num;
			goto s;
		}
		edge = edge->next;
	}
	if (edge == nullptr)
	{
		isMatched = false;
		goto out;
	}

out:
	return isMatched;
}

bool RE::search(string test_str, vector<string> &result)
{
	result.clear();
	pos = 0;
	this->test_str = test_str;
	int state = 0;
	MDFA_Edge *edge = nullptr;
	deque<int> stk;

start:
	matchedString.clear();
	state = 0;
	stk.clear();
	stk.push_back(-1);

s:
	currentChar = getNextChar();
	matchedString += currentChar;
	if (nodes[state]->isAccept == true)
		stk.clear();
	stk.push_back(state);
	edge = nodes[state]->edges;
	while (edge != nullptr)
	{
		if (edge->c == currentChar)
		{
			state = edge->to->num;
			goto s;
		}
		edge = edge->next;
	}
	if (edge == nullptr)
		goto out;

out:
	while (state != -1 && !nodes[state]->isAccept)
	{
		stk.pop_back();
		state = stk.back();
		if (!matchedString.empty())
			matchedString.pop_back();
		rollBack();
	}
	if (state == -1)
	{
		if (currentChar == '\0')
		{
			if (!result.empty())
				return true;
			else
				return false;
		}
		currentChar = getNextChar();
		goto start;
	}

	if (nodes[state]->isAccept)
	{
		matchedString.pop_back();
		result.push_back(matchedString);
		if (currentChar == '\0')
		{
			if (!result.empty())
				return true;
			else
				return false;
		}
		rollBack();
		goto start;
	}
}
