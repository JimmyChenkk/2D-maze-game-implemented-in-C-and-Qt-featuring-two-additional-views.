#pragma once
#include<vector>
#include <stack>
#include <QString>
#include <QObject>
#include "point.h"
using namespace std;


class mazedata : public QObject
{
		Q_OBJECT
private:
	int maxrow = 17;//迷宫尺寸
	int maxcol = 17;//迷宫尺寸
	int maypathcount = 0;//生成迷宫涉及
	int start = 0;//入口所在行
	int score = 0;//特殊机构分数
	int direction = 0;//玩家当前的朝向 每次重置后重置为向右

	//以下三个计数 为view3d相关
	int countroad = 0;
	int countleftwall = 1;
	int countrightwall = 1;

	vector<vector<point>> maze= vector<vector<point>>(maxrow, vector<point>(maxcol, point()));//数据结构是一个二维向量 作为mazedata类的私有变量
	stack<point> findpath;//生成迷宫涉及
	vector<point> player;//记录玩家走过之处
	vector<point> keyway;//记录答案路径
signals:
	//三个信号函数 对应的槽函数详见LDRproject.cpp
	void hitWall();
	void success();
	void out();
public:
	explicit mazedata(QObject* parent = nullptr) : QObject(parent) { createmaze(); };
	~mazedata(){}
	int getmaxrow() { return maxrow; }
	int getmaxcol() { return maxcol; }
	vector<vector<point>> getmaze() { return maze; };
	int getstart() { return start; };
	int getscore() { return score; };
	//以上均为用函数获取各种私有变量

	void resetmaypathcount() { maypathcount = 0; };
	void createmaze();//生成迷宫
	int initmaze();//初始化迷宫
	int getstart(int u) { start = u; };//设置入口
	int directions();//随机返回可用方向 生成迷宫涉及
	void setend();//随机出口
	void deadend();//找到死路 用于放置特殊机构
	
	string translatetext(string order);//解码器函数
	void moving(string translatedsteps);//移动函数
	bool movingcheck(int row,int col);//检查/判定移动所到位置
	void movedpoint(int row, int col);//根据movingcheck的结果 操作player向量
	void initstackplayer();//初始化向量
	void printstackplayer();//记录玩家所到之处的向量里的内容的标记全改为player
	void eraser();//记录玩家所到之处的向量里的内容的标记全从player改为path
	void clearstackplayer();//清空记录玩家走过之处的向量

	void findkeyway();//答案寻路函数
	void clearkeyway();//清空记录答案的向量

	//以下为view3d相关
	void Countroad();
	void Countleftwall();
	void Countrightwall();
	int getCountroad() {return countroad;};
	int getCountleftwall() { return countleftwall; };
	int getCountrightwall() { return countrightwall; };
};

