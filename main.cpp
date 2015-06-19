#include "re.h"
#include <iostream>

using namespace std;

int main()
{
	RE re("ab|abcde");
	string test_str;
	test_str = "abcde";
	if (re.match(test_str))
		cout << test_str << "匹配成功" << endl;
	else
		cout << test_str << "匹配不成功" << endl;
	
	test_str = "abcd";
	if (re.match(test_str))
		cout << test_str << "匹配成功" << endl;
	else
		cout << test_str << "匹配不成功" << endl;

	test_str = "aadacaaaababcabcabcdabcde";
	vector<string> result;
	if (re.search(test_str, result))
	{
		for (auto it = result.begin(); it != result.end(); ++it)
			cout << *it << endl;
	}

	re.replace("a(b|c)*");
	test_str = "abcbcbc";
	if (re.match(test_str))
		cout << test_str << "匹配成功" << endl;
	else
		cout << test_str << "匹配不成功" << endl;
	test_str = "abcbcd";
	if (re.match(test_str))
		cout << test_str << "匹配成功" << endl;
	else
		cout << test_str << "匹配不成功" << endl;

	test_str = "abcbcdeaaabcbcbccccbacbfew";
	if (re.search(test_str, result))
	{
		for (auto it = result.begin(); it != result.end(); ++it)
			cout << *it << endl;
	}
	return 0;
}
