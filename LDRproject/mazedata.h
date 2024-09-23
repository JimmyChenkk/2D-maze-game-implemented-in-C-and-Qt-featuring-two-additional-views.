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
	int maxrow = 17;//�Թ��ߴ�
	int maxcol = 17;//�Թ��ߴ�
	int maypathcount = 0;//�����Թ��漰
	int start = 0;//���������
	int score = 0;//�����������
	int direction = 0;//��ҵ�ǰ�ĳ��� ÿ�����ú�����Ϊ����

	//������������ Ϊview3d���
	int countroad = 0;
	int countleftwall = 1;
	int countrightwall = 1;

	vector<vector<point>> maze= vector<vector<point>>(maxrow, vector<point>(maxcol, point()));//���ݽṹ��һ����ά���� ��Ϊmazedata���˽�б���
	stack<point> findpath;//�����Թ��漰
	vector<point> player;//��¼����߹�֮��
	vector<point> keyway;//��¼��·��
signals:
	//�����źź��� ��Ӧ�Ĳۺ������LDRproject.cpp
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
	//���Ͼ�Ϊ�ú�����ȡ����˽�б���

	void resetmaypathcount() { maypathcount = 0; };
	void createmaze();//�����Թ�
	int initmaze();//��ʼ���Թ�
	int getstart(int u) { start = u; };//�������
	int directions();//������ؿ��÷��� �����Թ��漰
	void setend();//�������
	void deadend();//�ҵ���· ���ڷ����������
	
	string translatetext(string order);//����������
	void moving(string translatedsteps);//�ƶ�����
	bool movingcheck(int row,int col);//���/�ж��ƶ�����λ��
	void movedpoint(int row, int col);//����movingcheck�Ľ�� ����player����
	void initstackplayer();//��ʼ������
	void printstackplayer();//��¼�������֮��������������ݵı��ȫ��Ϊplayer
	void eraser();//��¼�������֮��������������ݵı��ȫ��player��Ϊpath
	void clearstackplayer();//��ռ�¼����߹�֮��������

	void findkeyway();//��Ѱ·����
	void clearkeyway();//��ռ�¼�𰸵�����

	//����Ϊview3d���
	void Countroad();
	void Countleftwall();
	void Countrightwall();
	int getCountroad() {return countroad;};
	int getCountleftwall() { return countleftwall; };
	int getCountrightwall() { return countrightwall; };
};

