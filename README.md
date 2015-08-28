# My-RegexEngine
# 6月19日
  能够识别选择、连接和闭包三种运算
  只有基本的匹配功能, 没有错误检测和异常处理的功能
  以后有时间慢慢完善
 
## 举例
```C++
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
```

###运行结果:
![图片](https://github.com/Xiang1993/C-Mini-Compiler/blob/master/folder/4.jpg)

