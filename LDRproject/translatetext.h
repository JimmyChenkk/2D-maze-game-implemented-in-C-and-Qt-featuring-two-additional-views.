#pragma once
#include<iostream>
#include<string>
#include<cstring>
#include<string.h>
#include<stack>
#include<vector>
//解码器为张哲傲同学编写 主要用到栈 详见报告
using namespace std;
string decoder(string a);
int getlen(string a);
/******************************************************************************************/
int getlen(string a)
{
	int len = 0;
	for (int i = 0; a[i] != NULL; i++)
	{
		len++;
	}
	//cout << "长度：" << len << endl;
	return len;
}
bool have(string a)        //判断有没有括号
{
	for (int i = 0; i < getlen(a); i++)
	{
		if (a[i] == '(' || a[i] == ')')
			return true;
	}
	return false;
}
bool check(string a)               //判断括号是否匹配
{
	stack<char>s;
	for (int i = 0; i < getlen(a); i++)
	{
		if (a[i] == '(')
		{
			s.push(a[i]);
		}
		if (a[i] == ')')
		{
			if (s.empty())
			{
				return false;
			}
			if (s.top() == '(')
			{
				s.pop();
			}
			else
			{
				return false;
			}
		}
	}
	if (s.empty())
	{
		return true;
	}
	else
		return false;
}
bool safe(string a)     //判断字符串是否合法
{
	int len = getlen(a);
	for (int i = 0; i < len; i++)
	{
		if (a[i] >= 48 && a[i] <= 57)
		{
			if (i == 0) {
				cout << "数字出现在首位，错误1" << endl;
				return false;
			}
			else
				if (a[i - 1] == '(')
				{
					cout << "数字前出现左括号，错误2" << endl;
					return false;
				}
		}
		if (a[i] != '(' && a[i] != ')' && a[i] != 'L' && a[i] != 'D' && a[i] != 'R' && a[i] < '0' && a[i] > '9' && a[i] != '*' && a[i] != 'l' && a[i] != 'r')
		{
			cout << "出现非法字符，错误3" << a[i] << endl;
			return false;
		}
	}
	if (!check(a))
	{
		cout << "括号不匹配，错误4" << endl;
		return false;

	}
	return true;
}
string decoder(string a)
{
	int len = getlen(a);
	string err = "错误";
	if (!safe(a))
	{
		return err;
	}
	if (!have(a)) {
		string b;
		int count = 0;
		int sum = 0;
		vector<int>v;
		for (int i = 0; i < len; i++)
		{
			if (a[i] < 48 || a[i]>57) {
				b += a[i];

			}
			else {
				count = 0;
				sum = 0;
				v.clear();
				for (int k = 0; a[i + k] <= 57 && a[i + k] >= 48; k++) {
					int x;
					x = a[i + k] - 48;
					count++;
					v.push_back(x);
				}
				for (int t = 0; t < count; t++)
				{
					sum += v[t] * pow(10, count - 1 - t);
				}
				for (int j = 0; j < sum - 1; j++)
				{
					b += a[i - 1];
					//cout << a[i - 1];
				}
				i += count - 1;
				//b += a[i];
				//cout << a[i];
			}
		}
		//cout << "QQQQQQQQQQQQQQQ" << b << endl;
		return b;
	}
}
string decoder2(string a)
{
	stack<char>s;
	string c;
	string str = "错误";
	int len = getlen(a);
	if (!safe(a))
	{
		return str;
	}
	if (!have(a)) {
		string e = decoder(a);
		return e;
	}
	for (int i = 0; i < len; i++)
	{
		string b;
		if (a[i] >= 48 && a[i] <= 57 && a[i - 1] != ')')     //括号内遇到数字
		{
			int sum1 = 0;
			int x, count1 = 0;
			vector<int>v1;
			sum1 = 0;
			count1 = 0;
			x = 0;
			v1.clear();
			for (int t = 0; a[i + t] >= 48 && a[i + t] <= 57; t++)
			{
				x = a[i + t] - 48;
				v1.push_back(x);
				count1++;
				//cout << "x=" << x << endl;
			}
			if (!v1.empty())
			{
				for (int j = 0; j < count1; j++)
				{
					sum1 += pow(10, count1 - 1 - j) * v1[j];
				}
			}
			for (int t = 0; t < sum1 - 1; t++) {

				s.push(a[i - 1]);
			}
			i += count1 - 1;
			//cout << "sum1=" << sum1 << endl;
		}
		else {
			if (a[i] != ')')
			{
				s.push(a[i]);
			}
			else
			{
				int x;                            //提取数字，判断应该重复几遍
				if (i == len - 1) {
					x = 1;
				}
				else
				{
					int count = 0;//位数
					int sum = 0;        //分离数字
					vector<int>v;
					count = 0;
					sum = 0;
					v.clear();
					for (int k = 1; a[i + k] >= 48 && a[i + k] <= 57; k++) {
						count++;
						x = a[i + k] - 48;
						v.push_back(x);
					}
					if (!v.empty())
					{
						for (int j = 0; j < count; j++)
						{
							sum += pow(10, count - 1 - j) * v[j];
						}
						x = sum;
					}
					i += count;
				}
				while (s.top() != '(') {
					b += s.top();                 //这里
					s.pop();
				}
				s.pop();                 //把左括号出栈
				for (int t = 0; t < x; t++) {
					for (int k = getlen(b) - 1; k >= 0; k--)
					{
						if (b[k] != '(') {
							s.push(b[k]);
						}
					}
				}
				//i+=1;
			}
		}
	}
	while (!s.empty())         //全出栈
	{
		c += s.top();
		s.pop();
	}
	string d;
	for (int i = 0; i < getlen(c); i++)     //倒序变成正序
	{
		d += c[getlen(c) - 1 - i];
	}
	return d;
}