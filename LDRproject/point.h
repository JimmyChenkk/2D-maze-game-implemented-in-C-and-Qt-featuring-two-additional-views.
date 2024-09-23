#pragma once
class point
{
public:
	enum class State
	{wall,maywall,path,maypath,start,end,player,trap,food,};//记录每个元素在迷宫中充当的角色是什么
private:
	State pointstate = State::wall;
	int row = 0;//记录所在行
	int col = 0;//记录所在列
	bool visited = false;//记录是否被访问过 答案寻路涉及
	bool key = false;//记录是否是答案路径 答案寻路涉及
public:
	void setpointstate(State ps) { pointstate = ps; }//用函数改变私有变量pointstate
	void setrow(int r) { row = r; }//用函数改变私有变量 所在行
	void setcol(int c) { col = c; }//用函数改变私有变量 所在列
	void setpointmessage(State ps, int r, int c)//以上三个参数一起改变
	{
		setpointstate(ps);
		setrow(r);
		setcol(c);
	}

	State getpointstate() { return pointstate; }//用函数获取私有变量pointstate
	int getrow() { return row; }//用函数获取私有变量 所在行
	int getcol() { return col; }//用函数获取私有变量 所在列

	void changevisited(bool t) { visited = t; }//用函数改变私有变量 是否访问
	void changekey(bool t) { key = t; }//用函数改变私有变量 是否答案
	bool getvisited() { return visited; }//用函数获取私有变量 所在行
	bool getkey() { return key; }//用函数获取私有变量 所在行
	
	point() {}//构造
	~point() {}//析构
};
