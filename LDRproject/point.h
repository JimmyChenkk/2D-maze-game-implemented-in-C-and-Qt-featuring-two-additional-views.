#pragma once
class point
{
public:
	enum class State
	{wall,maywall,path,maypath,start,end,player,trap,food,};//��¼ÿ��Ԫ�����Թ��г䵱�Ľ�ɫ��ʲô
private:
	State pointstate = State::wall;
	int row = 0;//��¼������
	int col = 0;//��¼������
	bool visited = false;//��¼�Ƿ񱻷��ʹ� ��Ѱ·�漰
	bool key = false;//��¼�Ƿ��Ǵ�·�� ��Ѱ·�漰
public:
	void setpointstate(State ps) { pointstate = ps; }//�ú����ı�˽�б���pointstate
	void setrow(int r) { row = r; }//�ú����ı�˽�б��� ������
	void setcol(int c) { col = c; }//�ú����ı�˽�б��� ������
	void setpointmessage(State ps, int r, int c)//������������һ��ı�
	{
		setpointstate(ps);
		setrow(r);
		setcol(c);
	}

	State getpointstate() { return pointstate; }//�ú�����ȡ˽�б���pointstate
	int getrow() { return row; }//�ú�����ȡ˽�б��� ������
	int getcol() { return col; }//�ú�����ȡ˽�б��� ������

	void changevisited(bool t) { visited = t; }//�ú����ı�˽�б��� �Ƿ����
	void changekey(bool t) { key = t; }//�ú����ı�˽�б��� �Ƿ��
	bool getvisited() { return visited; }//�ú�����ȡ˽�б��� ������
	bool getkey() { return key; }//�ú�����ȡ˽�б��� ������
	
	point() {}//����
	~point() {}//����
};
