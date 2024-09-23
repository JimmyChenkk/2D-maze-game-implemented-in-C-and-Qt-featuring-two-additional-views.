#include "mazedata.h"
#include "translatetext.h"
#include <stack>
#include <vector>
#include <ctime>
//本项目中方向的处理逻辑都为 右0 上1 左2 下3
//左转就是++
//右转就是--
//为了防止负数以及控制在0123这四个数中 计算后还要让4取余 以余数的0123来判断方向

//https://zhuanlan.zhihu.com/p/27381213 ,<—地图生成用的是这篇知乎中的方法2
void mazedata::createmaze()//原理的知乎链接已附上↑
{
	int pathstart = initmaze();//初始化标记 为生成迷宫准备
	findpath.push(maze[pathstart][1]);//推入迷宫入口 防止top()读取空栈报错
	do
	{
		int d = directions();//方向
		if (d == 0)//右
		{
			maze[findpath.top().getrow() - 2][findpath.top().getcol()].setpointmessage(point::State::path, findpath.top().getrow() - 2, findpath.top().getcol());//设定元素角色
			maze[findpath.top().getrow() - 1][findpath.top().getcol()].setpointmessage(point::State::path, findpath.top().getrow() - 1, findpath.top().getcol());//设定元素角色
			findpath.push(maze[findpath.top().getrow() - 2][findpath.top().getcol()]);//入记录path的栈
			maypathcount--;
		}
		else if (d == 1)//上
		{
			maze[findpath.top().getrow() + 2][findpath.top().getcol()].setpointmessage(point::State::path, findpath.top().getrow() + 2, findpath.top().getcol());
			maze[findpath.top().getrow() + 1][findpath.top().getcol()].setpointmessage(point::State::path, findpath.top().getrow() + 1, findpath.top().getcol());
			findpath.push(maze[findpath.top().getrow() + 2][findpath.top().getcol()]);
			maypathcount--;
		}
		else if (d == 2)//左
		{
			maze[findpath.top().getrow()][findpath.top().getcol() - 2].setpointmessage(point::State::path, findpath.top().getrow(), findpath.top().getcol() - 2);
			maze[findpath.top().getrow()][findpath.top().getcol() - 1].setpointmessage(point::State::path, findpath.top().getrow(), findpath.top().getcol() - 1);
			findpath.push(maze[findpath.top().getrow()][findpath.top().getcol() - 2]);
			maypathcount--;
		}
		else if (d == 3)//下
		{
			maze[findpath.top().getrow()][findpath.top().getcol() + 2].setpointmessage(point::State::path, findpath.top().getrow(), findpath.top().getcol() + 2);
			maze[findpath.top().getrow()][findpath.top().getcol() + 1].setpointmessage(point::State::path, findpath.top().getrow(), findpath.top().getcol() + 1);
			findpath.push(maze[findpath.top().getrow()][findpath.top().getcol() + 2]);
			maypathcount--;
		}
		else if (d == -1)//没可继续开路的方向
		{
			findpath.pop();//栈顶出栈 直到找到路
		}
	} while (maypathcount > 1);
	setend();//设置出口
	deadend();//找死路 用来放特殊机构
	for (int row = 1; row < maxrow - 1; row++)//把生成时用的maywall标记全改为wall变为真正的墙
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

int mazedata::directions() {//随机返回方向 随机挖出迷宫
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
	if (directionlist.size() == 0) result = -1;//栈空 那就是没找到 就返回-1
	else result = directionlist[rand() % ((int)directionlist.size())];//随机返回一个方向
	return result;
}

int mazedata::initmaze()//生成前准备 就是有些点注定是路或者墙 具体可参考知乎链接
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
			maze[u][0].setpointmessage(point::State::start, u, 0);//随机设定入口
			start = u;
			return u;
		}
	}
}

void mazedata::setend()//最后一列的path随机选一个 然后它右边就是end了
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

string mazedata::translatetext(string order)//解码器函数接入
{
	string b;
	b = decoder2(order);
	return b;
}

void mazedata::moving(string translatedsteps)
{
	int remainder = 0;
	for (char c : translatedsteps)//移动函数就是先看方向 再看传进来的字符是LDR哪个 LR只需通过加减改变方向即可 而D则要先判断再操作player向量
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
			//方向的处理原理见顶部↑↑
		case'R':
			direction--;
			break;
		case'L':
			direction++;
			break;
		}
	}

	//以下view3d相关 每次移动玩要初始化 重新数数
	countroad = 0;
	countleftwall = 0;
	countrightwall = 0;
	Countroad();
	Countleftwall();
	Countrightwall();
}

bool mazedata::movingcheck(int row, int col)
{
	if (row < 0 || col < 0)//从入口出去了 出界！
	{
		emit out();//发出信号函数
		return false;
	}
	if (maze[row][col].getpointstate() == point::State::wall || maze[row][col].getpointstate() == point::State::maywall)//下一格子的角色是墙 撞墙！
	{
		emit hitWall();//发出信号函数
		return false;
	}
	if (maze[row][col].getpointstate() == point::State::end)//下一个是出口 走出去了！
	{
		emit success();//发出信号函数
		return false;
	}
	if (maze[row][col].getpointstate() == point::State::food)//下一个是特殊机构 加分
	{
		score += 10;
	}
	if (maze[row][col].getpointstate() == point::State::trap)//trap最后没有做 因为觉得绕进死路为了加分是合理的 为了减分就不合理了
	{
		score -= 10;
	}
	return true;//有大问题就是直接false 上面moving函数也return了不走了 没啥问题就return true
}

void mazedata::movedpoint(int row, int col)//对player向量的操作
{
	if (player.size() > 2 && row == player[player.size() - 2].getrow() && col == player[player.size() - 2].getcol())
	{
		player.pop_back();//核心！ 回头走怎么实现的 由于迷宫没有环路 所以回头走就是和倒数第二个元素的内容比较一下 一样说明走回头路了 那末尾元素就不算所到之处了 移出向量
	}
	else
	{
		player.push_back(maze[row][col]);
	}
}


void mazedata::initstackplayer()
{
	player.push_back(maze[start][0]);//防止访问空向量报错
}

void mazedata::printstackplayer()//player向量在移动判定时只出栈入栈 最后统一遍历标记player 用于涂色
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

void mazedata::deadend()//这个算法不佳 只是遍历所有path 找出谁三个方向都是墙 那么他就是死路
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

void mazedata::findkeyway()//找答案路
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
		if (maze[keyway.back().getrow()][keyway.back().getcol() + 1].getpointstate() == point::State::end)//万一找到出口了 赶紧结束函数
		{
			keyway.push_back(maze[keyway.back().getrow()][keyway.back().getcol() + 1]);
			maze[keyway.back().getrow()][keyway.back().getcol()].changevisited(true);
			k = false;
		}
		//以下四段就是四个方向 逻辑一样 都是满足不是墙而且没访问过才可以入栈
		else if (maze[keyway.back().getrow()][keyway.back().getcol() + 1].getpointstate() != point::State::wall && maze[keyway.back().getrow()][keyway.back().getcol() + 1].getvisited() == false)
		{

			keyway.push_back(maze[keyway.back().getrow()][keyway.back().getcol() + 1]);
			maze[keyway.back().getrow()][keyway.back().getcol()].changevisited(true);//记得修改访问性 以及 注意此时栈顶就是目标元素 不用加减了
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
		if (count == 0)//count就是找没找到 前面只要找到就会count++ 那么count=0就是没找到 那就出栈到再找到为止
		{
			keyway.pop_back();
		}
	}
	for (int i = 0; i < keyway.size(); i++)
	{
		maze[keyway[i].getrow()][keyway[i].getcol()].changekey(true);
	}
}

void mazedata::clearkeyway()//答案数据都要还原 然后再清空 因为要访问不止一次 所以我用了向量而不是栈 栈出栈了就没有了 除了栈顶也不能访问其中其他内容
{
	for (int i = 0; i < keyway.size(); i++)
	{
		maze[keyway[i].getrow()][keyway[i].getcol()].changekey(false);
		maze[keyway[i].getrow()][keyway[i].getcol()].changevisited(false);
	}
	keyway.clear();
}


//以下为view3d相关 其实就是数一下面前有几格路 左右手边各有几格墙
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
