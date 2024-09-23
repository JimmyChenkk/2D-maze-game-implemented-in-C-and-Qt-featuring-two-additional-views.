#pragma once
#include<iostream>
#include<string>
#include<cstring>
#include<string.h>
#include<stack>
#include<vector>
//������Ϊ���ܰ�ͬѧ��д ��Ҫ�õ�ջ �������
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
	//cout << "���ȣ�" << len << endl;
	return len;
}
bool have(string a)        //�ж���û������
{
	for (int i = 0; i < getlen(a); i++)
	{
		if (a[i] == '(' || a[i] == ')')
			return true;
	}
	return false;
}
bool check(string a)               //�ж������Ƿ�ƥ��
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
bool safe(string a)     //�ж��ַ����Ƿ�Ϸ�
{
	int len = getlen(a);
	for (int i = 0; i < len; i++)
	{
		if (a[i] >= 48 && a[i] <= 57)
		{
			if (i == 0) {
				cout << "���ֳ�������λ������1" << endl;
				return false;
			}
			else
				if (a[i - 1] == '(')
				{
					cout << "����ǰ���������ţ�����2" << endl;
					return false;
				}
		}
		if (a[i] != '(' && a[i] != ')' && a[i] != 'L' && a[i] != 'D' && a[i] != 'R' && a[i] < '0' && a[i] > '9' && a[i] != '*' && a[i] != 'l' && a[i] != 'r')
		{
			cout << "���ַǷ��ַ�������3" << a[i] << endl;
			return false;
		}
	}
	if (!check(a))
	{
		cout << "���Ų�ƥ�䣬����4" << endl;
		return false;

	}
	return true;
}
string decoder(string a)
{
	int len = getlen(a);
	string err = "����";
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
	string str = "����";
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
		if (a[i] >= 48 && a[i] <= 57 && a[i - 1] != ')')     //��������������
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
				int x;                            //��ȡ���֣��ж�Ӧ���ظ�����
				if (i == len - 1) {
					x = 1;
				}
				else
				{
					int count = 0;//λ��
					int sum = 0;        //��������
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
					b += s.top();                 //����
					s.pop();
				}
				s.pop();                 //�������ų�ջ
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
	while (!s.empty())         //ȫ��ջ
	{
		c += s.top();
		s.pop();
	}
	string d;
	for (int i = 0; i < getlen(c); i++)     //����������
	{
		d += c[getlen(c) - 1 - i];
	}
	return d;
}