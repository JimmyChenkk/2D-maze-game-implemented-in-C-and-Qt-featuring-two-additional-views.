#include "mazedata.h"
#include "translatetext.h"
#include <stack>
#include <vector>
#include <ctime>
//����Ŀ�з���Ĵ����߼���Ϊ ��0 ��1 ��2 ��3
//��ת����++
//��ת����--
//Ϊ�˷�ֹ�����Լ�������0123���ĸ����� �����Ҫ��4ȡ�� ��������0123���жϷ���

//https://zhuanlan.zhihu.com/p/27381213 ,<����ͼ�����õ�����ƪ֪���еķ���2
void mazedata::createmaze()//ԭ���֪�������Ѹ��ϡ�
{
	int pathstart = initmaze();//��ʼ����� Ϊ�����Թ�׼��
	findpath.push(maze[pathstart][1]);//�����Թ���� ��ֹtop()��ȡ��ջ����
	do
	{
		int d = directions();//����
		if (d == 0)//��
		{
			maze[findpath.top().getrow() - 2][findpath.top().getcol()].setpointmessage(point::State::path, findpath.top().getrow() - 2, findpath.top().getcol());//�趨Ԫ�ؽ�ɫ
			maze[findpath.top().getrow() - 1][findpath.top().getcol()].setpointmessage(point::State::path, findpath.top().getrow() - 1, findpath.top().getcol());//�趨Ԫ�ؽ�ɫ
			findpath.push(maze[findpath.top().getrow() - 2][findpath.top().getcol()]);//���¼path��ջ
			maypathcount--;
		}
		else if (d == 1)//��
		{
			maze[findpath.top().getrow() + 2][findpath.top().getcol()].setpointmessage(point::State::path, findpath.top().getrow() + 2, findpath.top().getcol());
			maze[findpath.top().getrow() + 1][findpath.top().getcol()].setpointmessage(point::State::path, findpath.top().getrow() + 1, findpath.top().getcol());
			findpath.push(maze[findpath.top().getrow() + 2][findpath.top().getcol()]);
			maypathcount--;
		}
		else if (d == 2)//��
		{
			maze[findpath.top().getrow()][findpath.top().getcol() - 2].setpointmessage(point::State::path, findpath.top().getrow(), findpath.top().getcol() - 2);
			maze[findpath.top().getrow()][findpath.top().getcol() - 1].setpointmessage(point::State::path, findpath.top().getrow(), findpath.top().getcol() - 1);
			findpath.push(maze[findpath.top().getrow()][findpath.top().getcol() - 2]);
			maypathcount--;
		}
		else if (d == 3)//��
		{
			maze[findpath.top().getrow()][findpath.top().getcol() + 2].setpointmessage(point::State::path, findpath.top().getrow(), findpath.top().getcol() + 2);
			maze[findpath.top().getrow()][findpath.top().getcol() + 1].setpointmessage(point::State::path, findpath.top().getrow(), findpath.top().getcol() + 1);
			findpath.push(maze[findpath.top().getrow()][findpath.top().getcol() + 2]);
			maypathcount--;
		}
		else if (d == -1)//û�ɼ�����·�ķ���
		{
			findpath.pop();//ջ����ջ ֱ���ҵ�·
		}
	} while (maypathcount > 1);
	setend();//���ó���
	deadend();//����· �������������
	for (int row = 1; row < maxrow - 1; row++)//������ʱ�õ�maywall���ȫ��Ϊwall��Ϊ������ǽ
	{
		for (int col = 1; col < maxcol - 1; col++)
		{
			if (maze[row][col].getpointstate() == point::State::maywall)
			{
				maze[row][col].setpointmessage(point::State::wall, row, col);
			}
		}
	}
}

int mazedata::directions() {//������ط��� ����ڳ��Թ�
	vector <int> directionlist;
	int row = findpath.top().getrow();
	int col = findpath.top().getcol();

	if (row - 2 > 0
		&& maze[row - 2][col].getpointstate() == point::State::maypath
		&& maze[row - 1][col].getpointstate() == point::State::maywall)
		directionlist.push_back(0);//0 up
	if (row + 2 < maxrow - 1
		&& maze[row + 2][col].getpointstate() == point::State::maypath
		&& maze[row + 1][col].getpointstate() == point::State::maywall)
		directionlist.push_back(1);//1 down
	if (col - 2 > 0
		&& maze[row][col - 2].getpointstate() == point::State::maypath
		&& maze[row][col - 1].getpointstate() == point::State::maywall)
		directionlist.push_back(2);//2 left
	if (col + 2 < maxcol - 1
		&& maze[row][col + 2].getpointstate() == point::State::maypath
		&& maze[row][col + 1].getpointstate() == point::State::maywall)
		directionlist.push_back(3);// 3 right

	int result = 0;
	if (directionlist.size() == 0) result = -1;//ջ�� �Ǿ���û�ҵ� �ͷ���-1
	else result = directionlist[rand() % ((int)directionlist.size())];//�������һ������
	return result;
}

int mazedata::initmaze()//����ǰ׼�� ������Щ��ע����·����ǽ ����ɲο�֪������
{
	direction = 0;
	score = 0;
	countroad = 0;
	countleftwall = 0;
	countrightwall = 0;
	for (int row = 0; row < maxrow; row++)
	{
		maze[row][0].setpointmessage(point::State::wall, row, 0);
		maze[row][maxcol - 1].setpointmessage(point::State::wall, row, maxcol - 1);
	}
	for (int col = 0; col < maxcol; col++)
	{
		maze[0][col].setpointmessage(point::State::wall, 0, col);
		maze[maxrow - 1][col].setpointmessage(point::State::wall, maxrow - 1, col);
	}
	for (int row = 1; row < maxrow - 1; row++)
	{
		for (int col = 1; col < maxcol - 1; col++)
		{
			if (row % 2 != 0 && col % 2 != 0)
			{
				maze[row][col].setpointmessage(point::State::maypath, row, col);
				maze[row][col].changevisited(false);
				maze[row][col].changekey(false);
				maypathcount++;
			}
			else
			{
				maze[row][col].setpointmessage(point::State::maywall, row, col);
				maze[row][col].changevisited(false);
				maze[row][col].changekey(false);
			}
		}
	}
	srand(time(0));
	for (;;)
	{
		int u = (rand() % maxrow);
		if (maze[u][1].getpointstate() == point::State::maypath)
		{
			maze[u][1].setpointmessage(point::State::path, u, 1);
			maze[u][0].setpointmessage(point::State::start, u, 0);//����趨���
			start = u;
			return u;
		}
	}
}

void mazedata::setend()//���һ�е�path���ѡһ�� Ȼ�����ұ߾���end��
{
	for (;;)
	{
		int u = (rand() % maxrow);
		if (maze[u][maxcol - 2].getpointstate() == point::State::path)
		{
			maze[u][maxcol - 2].setpointmessage(point::State::path, u, maxcol - 2);
			maze[u][maxcol - 1].setpointmessage(point::State::end, u, maxcol - 1);
			break;
		}
	}
}

string mazedata::translatetext(string order)//��������������
{
	string b;
	b = decoder2(order);
	return b;
}

void mazedata::moving(string translatedsteps)
{
	int remainder = 0;
	for (char c : translatedsteps)//�ƶ����������ȿ����� �ٿ����������ַ���LDR�ĸ� LRֻ��ͨ���Ӽ��ı䷽�򼴿� ��D��Ҫ���ж��ٲ���player����
	{
		remainder = direction % 4;
		while (remainder < 0)
		{
			remainder += 4;
		}
		switch (c)
		{
		case'D':
			switch (remainder)
			{
			case 0:
				if (movingcheck(player.back().getrow(), player.back().getcol() + 1) == true)
				{
					movedpoint(player.back().getrow(), player.back().getcol() + 1);
				}
				else { return; }
				break;
			case 1:
				if (movingcheck(player.back().getrow() - 1, player.back().getcol()) == true)
				{
					movedpoint(player.back().getrow() - 1, player.back().getcol());
				}
				else { return; }
				break;
			case 2:
				if (movingcheck(player.back().getrow(), player.back().getcol() - 1) == true)
				{
					movedpoint(player.back().getrow(), player.back().getcol() - 1);
				}
				else { return; }
				break;
			case 3:
				if (movingcheck(player.back().getrow() + 1, player.back().getcol()) == true)
				{
					movedpoint(player.back().getrow() + 1, player.back().getcol());
				}
				else { return; }
				break;
			}
			break;
			//����Ĵ���ԭ�����������
		case'R':
			direction--;
			break;
		case'L':
			direction++;
			break;
		}
	}

	//����view3d��� ÿ���ƶ���Ҫ��ʼ�� ��������
	countroad = 0;
	countleftwall = 0;
	countrightwall = 0;
	Countroad();
	Countleftwall();
	Countrightwall();
}

bool mazedata::movingcheck(int row, int col)
{
	if (row < 0 || col < 0)//����ڳ�ȥ�� ���磡
	{
		emit out();//�����źź���
		return false;
	}
	if (maze[row][col].getpointstate() == point::State::wall || maze[row][col].getpointstate() == point::State::maywall)//��һ���ӵĽ�ɫ��ǽ ײǽ��
	{
		emit hitWall();//�����źź���
		return false;
	}
	if (maze[row][col].getpointstate() == point::State::end)//��һ���ǳ��� �߳�ȥ�ˣ�
	{
		emit success();//�����źź���
		return false;
	}
	if (maze[row][col].getpointstate() == point::State::food)//��һ����������� �ӷ�
	{
		score += 10;
	}
	if (maze[row][col].getpointstate() == point::State::trap)//trap���û���� ��Ϊ�����ƽ���·Ϊ�˼ӷ��Ǻ���� Ϊ�˼��־Ͳ�������
	{
		score -= 10;
	}
	return true;//�д��������ֱ��false ����moving����Ҳreturn�˲����� ûɶ�����return true
}

void mazedata::movedpoint(int row, int col)//��player�����Ĳ���
{
	if (player.size() > 2 && row == player[player.size() - 2].getrow() && col == player[player.size() - 2].getcol())
	{
		player.pop_back();//���ģ� ��ͷ����ôʵ�ֵ� �����Թ�û�л�· ���Ի�ͷ�߾��Ǻ͵����ڶ���Ԫ�ص����ݱȽ�һ�� һ��˵���߻�ͷ·�� ��ĩβԪ�ؾͲ�������֮���� �Ƴ�����
	}
	else
	{
		player.push_back(maze[row][col]);
	}
}


void mazedata::initstackplayer()
{
	player.push_back(maze[start][0]);//��ֹ���ʿ���������
}

void mazedata::printstackplayer()//player�������ƶ��ж�ʱֻ��ջ��ջ ���ͳһ�������player ����Ϳɫ
{
	for (int i = 0; i < player.size(); i++)
	{
		maze[player[i].getrow()][player[i].getcol()].setpointmessage(point::State::player, player[i].getrow(), player[i].getcol());
	}
	maze[start][0].setpointmessage(point::State::start, start, 0);
}

void mazedata::clearstackplayer()
{
	player.clear();
}

void mazedata::eraser()
{
	for (int i = 0; i < player.size(); i++)
	{
		maze[player[i].getrow()][player[i].getcol()].setpointmessage(point::State::path, player[i].getrow(), player[i].getcol());
	}
}

void mazedata::deadend()//����㷨���� ֻ�Ǳ�������path �ҳ�˭����������ǽ ��ô��������·
{
	for (int row = 1; row < maxrow - 1; row++)
	{
		for (int col = 1; col < maxcol - 1; col++)
		{
			if (maze[row][col].getpointstate() == point::State::path)
			{
				int count = 0;
				if (maze[row + 1][col].getpointstate() == point::State::wall || maze[row + 1][col].getpointstate() == point::State::maywall)
					count++;
				if (maze[row - 1][col].getpointstate() == point::State::wall || maze[row - 1][col].getpointstate() == point::State::maywall)
					count++;
				if (maze[row][col + 1].getpointstate() == point::State::wall || maze[row][col + 1].getpointstate() == point::State::maywall)
					count++;
				if (maze[row][col - 1].getpointstate() == point::State::wall || maze[row][col - 1].getpointstate() == point::State::maywall)
					count++;
				if (count > 2)
				{
					maze[row][col].setpointmessage(point::State::food, row, col);
				}
			}
		}
	}
}

void mazedata::findkeyway()//�Ҵ�·
{
	keyway.clear();
	keyway.push_back(maze[start][0]);
	maze[start][0].changevisited(true);
	maze[start][0].changekey(true);
	int count = 0;
	bool k = true;
	while (k == true)
	{
		count = 0;
		if (maze[keyway.back().getrow()][keyway.back().getcol() + 1].getpointstate() == point::State::end)//��һ�ҵ������� �Ͻ���������
		{
			keyway.push_back(maze[keyway.back().getrow()][keyway.back().getcol() + 1]);
			maze[keyway.back().getrow()][keyway.back().getcol()].changevisited(true);
			k = false;
		}
		//�����Ķξ����ĸ����� �߼�һ�� �������㲻��ǽ����û���ʹ��ſ�����ջ
		else if (maze[keyway.back().getrow()][keyway.back().getcol() + 1].getpointstate() != point::State::wall && maze[keyway.back().getrow()][keyway.back().getcol() + 1].getvisited() == false)
		{

			keyway.push_back(maze[keyway.back().getrow()][keyway.back().getcol() + 1]);
			maze[keyway.back().getrow()][keyway.back().getcol()].changevisited(true);//�ǵ��޸ķ����� �Լ� ע���ʱջ������Ŀ��Ԫ�� ���üӼ���
			count++;
		}
		else if (maze[keyway.back().getrow()][keyway.back().getcol() - 1].getpointstate() != point::State::wall && maze[keyway.back().getrow()][keyway.back().getcol() - 1].getvisited() == false)
		{

			keyway.push_back(maze[keyway.back().getrow()][keyway.back().getcol() - 1]);
			maze[keyway.back().getrow()][keyway.back().getcol()].changevisited(true);
			count++;
		}

		else if (maze[keyway.back().getrow() + 1][keyway.back().getcol()].getpointstate() != point::State::wall && maze[keyway.back().getrow() + 1][keyway.back().getcol()].getvisited() == false)
		{
			keyway.push_back(maze[keyway.back().getrow() + 1][keyway.back().getcol()]);
			maze[keyway.back().getrow()][keyway.back().getcol()].changevisited(true);
			count++;
		}
		else if (maze[keyway.back().getrow() - 1][keyway.back().getcol()].getpointstate() != point::State::wall && maze[keyway.back().getrow() - 1][keyway.back().getcol()].getvisited() == false)
		{
			keyway.push_back(maze[keyway.back().getrow() - 1][keyway.back().getcol()]);
			maze[keyway.back().getrow()][keyway.back().getcol()].changevisited(true);
			count++;
		}
		if (count == 0)//count������û�ҵ� ǰ��ֻҪ�ҵ��ͻ�count++ ��ôcount=0����û�ҵ� �Ǿͳ�ջ�����ҵ�Ϊֹ
		{
			keyway.pop_back();
		}
	}
	for (int i = 0; i < keyway.size(); i++)
	{
		maze[keyway[i].getrow()][keyway[i].getcol()].changekey(true);
	}
}

void mazedata::clearkeyway()//�����ݶ�Ҫ��ԭ Ȼ������� ��ΪҪ���ʲ�ֹһ�� ��������������������ջ ջ��ջ�˾�û���� ����ջ��Ҳ���ܷ���������������
{
	for (int i = 0; i < keyway.size(); i++)
	{
		maze[keyway[i].getrow()][keyway[i].getcol()].changekey(false);
		maze[keyway[i].getrow()][keyway[i].getcol()].changevisited(false);
	}
	keyway.clear();
}


//����Ϊview3d��� ��ʵ������һ����ǰ�м���· �����ֱ߸��м���ǽ
void mazedata::Countroad()
{
	int row = player.back().getrow();
	int col = player.back().getcol();
	int remainder = direction % 4;
	while (remainder < 0)
	{
		remainder += 4;
	}
	if (remainder == 0)
	{
		for (int v = 1;; v++)
		{
			if (maze[row][col + v].getpointstate() == point::State::wall)
			{
				break;
			}
			if (maze[row][col + v].getpointstate() == point::State::path)
			{
				countroad++;
			}
		}

	}
	else if (remainder == 1)
	{
		for (int v = 1;; v++)
		{
			if (maze[row - v][col].getpointstate() == point::State::wall)
			{
				break;
			}
			if (maze[row - v][col].getpointstate() == point::State::path)
			{
				countroad++;
			}
		}

	}
	else if (remainder == 2)
	{
		for (int v = 1;; v++)
		{
			if (maze[row][col - v].getpointstate() == point::State::wall)
			{
				break;
			}
			if (maze[row][col - v].getpointstate() == point::State::path)
			{
				countroad++;
			}
		}

	}
	else if (remainder == 3)
	{
		for (int v = 1;; v++)
		{
			if (maze[row + v][col].getpointstate() == point::State::wall)
			{
				break;
			}
			if (maze[row + v][col].getpointstate() == point::State::path)
			{
				countroad++;
			}
		}

	}
}


void mazedata::Countleftwall()
{
	int row = player.back().getrow();
	int col = player.back().getcol();
	int remainder = direction % 4;
	while (remainder < 0)
	{
		remainder += 4;
	}
	if (remainder == 0)
	{
		for (int v = 0; v < countroad + 1; v++)
		{
			if (maze[row - 1][col + v].getpointstate() == point::State::path)
			{
				break;
			}
			if (maze[row - 1][col + v].getpointstate() == point::State::wall)
			{
				countleftwall++;
			}
		}
	}
	else if (remainder == 1)
	{
		for (int v = 0; v < countroad + 1; v++)
		{
			if (maze[row - v][col - 1].getpointstate() == point::State::path)
			{
				break;
			}
			if (maze[row - v][col - 1].getpointstate() == point::State::wall)
			{
				countleftwall++;
			}
		}
	}
	else if (remainder == 2)
	{
		for (int v = 0; v < countroad + 1; v++)
		{
			if (maze[row + 1][col - v].getpointstate() == point::State::path)
			{
				break;
			}
			if (maze[row + 1][col - v].getpointstate() == point::State::wall)
			{
				countleftwall++;
			}
		}
	}
	else if (remainder == 3)
	{
		for (int v = 0; v < countroad + 1; v++)
		{
			if (maze[row + v][col + 1].getpointstate() == point::State::path)
			{
				break;
			}
			if (maze[row + v][col + 1].getpointstate() == point::State::wall)
			{
				countleftwall++;
			}
		}
	}
}


void mazedata::Countrightwall()
{
	int row = player.back().getrow();
	int col = player.back().getcol();
	int remainder = direction % 4;
	while (remainder < 0)
	{
		remainder += 4;
	}
	if (remainder == 0)
	{
		for (int v = 0; v < countroad + 1; v++)
		{
			if (maze[row + 1][col + v].getpointstate() == point::State::path)
			{
				break;
			}
			if (maze[row + 1][col + v].getpointstate() == point::State::wall)
			{
				countrightwall++;
			}
		}
	}
	else if (remainder == 1)
	{
		for (int v = 0; v < countroad + 1; v++)
		{
			if (maze[row - v][col + 1].getpointstate() == point::State::path)
			{
				break;
			}
			if (maze[row - v][col + 1].getpointstate() == point::State::wall)
			{
				countrightwall++;
			}
		}
	}
	else if (remainder == 2)
	{
		for (int v = 0; v < countroad + 1; v++)
		{
			if (maze[row - 1][col - v].getpointstate() == point::State::path)
			{
				break;
			}
			if (maze[row - 1][col - v].getpointstate() == point::State::wall)
			{
				countrightwall++;
			}
		}
	}
	else if (remainder == 3)
	{
		for (int v = 0; v < countroad + 1; v++)
		{
			if (maze[row + v][col - 1].getpointstate() == point::State::path)
			{
				break;
			}
			if (maze[row + v][col - 1].getpointstate() == point::State::wall)
			{
				countrightwall++;
			}
		}
	}
}
