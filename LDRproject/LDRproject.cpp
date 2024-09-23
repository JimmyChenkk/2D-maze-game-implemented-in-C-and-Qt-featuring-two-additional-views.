#include "LDRproject.h"
#include "qgraphicsitem.h"
#include "qgraphicsscene.h"
#include "qnamespace.h"
#include "mazedata.h"
#include<QGraphicsRectItem>
#include<QThread>
#include<QKeyEvent>
#include<QMessageBox>
#include<vector>
#include<string>
#include<cstring>
#include<QString>
#include<QObject>
#include <QOpenGLWidget>
#include <GL/glut.h>
#include <math.h>
#include<iostream>
#include<time.h>
#include "mazedata.h"
#include <QOpenGLFunctions_3_3_Core>

LDRproject::LDRproject(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void LDRproject::run()
{
	//connect语句就是qt中链接信号与槽的语句
	//以下三段都是触发信号函数 然后QMessage出弹窗信息
	//依次为走到出口/撞墙/从入口出去出界
	QMainWindow::connect(maze, &mazedata::success, this, [=]()
		{
			int returnValue = maze->getscore();
	QString message = QString("出口，得分是: %1").arg(returnValue);
	QMessageBox::information(this, "", message);
	on_pushButton_2_clicked();
		});
	QMainWindow::connect(maze, &mazedata::hitWall, this, [=]()
		{
			int returnValue = maze->getscore();
	QString message = QString("撞墙，得分是: %1").arg(returnValue);
	QMessageBox::information(this, "", message);
	on_pushButton_2_clicked();
		});
	QMainWindow::connect(maze, &mazedata::out, this, [=]()
		{
			int returnValue = maze->getscore();
	QString message = QString("出界，得分是: %1").arg(returnValue);
	QMessageBox::information(this, "", message);
	on_pushButton_2_clicked();
		});
	maze->initstackplayer();//初始化记录玩家走过之处的向量
	drawmap();//绘制地图函数 定义在最底下↓
}

LDRproject::~LDRproject()
{

}

void LDRproject::on_pushButton_2_clicked()
{
	//点击重置后执行的的程序
	ui.lineEdit->clear();//输入框清空
	currentText = "";//初始化变量
	lastProcessedText = "";//初始化变量
	button3run = false;//初始化变量
	maze->clearstackplayer();//清空记录玩家走过之处的向量
	maze->resetmaypathcount();//重置maypathcount变量 生成迷宫涉及此变量
	maze->createmaze();//生成迷宫 定义在mazdata.cpp
	maze->initstackplayer();//初始化记录玩家走过之处的向量
	drawmap();//及时调用 重绘画面 否则静止不动体现不出效果
}

void LDRproject::on_pushButton_3_clicked()
{
	//点击答案后执行的的程序
	if (button3run == false)//保护写法 如果答案按钮没按过才能按
	{
		maze->findkeyway();//调用找答案函数 定义在mazedata.cpp
		button3run = true;//答案按钮按过了
	}
	drawmap();//及时调用 重绘画面 否则静止不动体现不出效果
}

void LDRproject::on_pushButton_4_clicked()
{
	//点击擦除答案后执行的的程序
	maze->clearkeyway();//清空记录答案路径的向量
	button3run = false;//重置答案按钮没按过
	drawmap();//及时调用 重绘画面 否则静止不动体现不出效果
}

void LDRproject::on_lineEdit_editingFinished()
{
	//点击确认或按回车后执行的程序
	//std::string currentText = ui.lineEdit->text().toStdString();
	currentText = ui.lineEdit->text().toStdString();
	// 计算新输入的部分
	std::string newInput = currentText.substr(lastProcessedText.length());
	// 更新上次处理的文本
	lastProcessedText = currentText;

	std::string translatedsteps = maze->translatetext(static_cast<string>(newInput));
	//新输入的内容接入解码器函数解码 去括号变为只有LDR的字符串

	maze->eraser();//记录玩家所到之处的向量里的内容的标记全从player改为path
	maze->moving(translatedsteps);//调用走动函数 定义在mazedata.cpp
	//std::string steps = ui.lineEdit->text().toStdString();
	//std::string translatedsteps = maze.translatetext(static_cast<string>(steps));
	//maze.moving(steps);
	maze->printstackplayer(); //记录玩家所到之处的向量里的内容的标记全改为player
	drawmap();//及时调用 重绘画面 否则静止不动体现不出效果
}

void LDRproject::drawmap()
{
	items.clear();
	if (gameBoard == nullptr)
	{
		this->gameBoard = new QGraphicsScene(this);
		ui.graphicsView->setScene(gameBoard);
	}
	gameBoard->clear();

	QPen pen;
	QGraphicsRectItem* scene = nullptr;
	int px = 0;
	int py = 0;

	vector<vector<point>> Maze = maze->getmaze();//获取二维数据结构

	for (int i = 0; i < maze->getmaxrow(); ++i)//行循环
	{
		items.push_back(QVector<QGraphicsRectItem*>{});
		for (int j = 0; j < maze->getmaxcol(); ++j)//列循环
		{
			scene = new QGraphicsRectItem(QRect{ py,px,maze->getmaxrow(),maze->getmaxcol() });
			//以下全部是通过函数获取pointstate 再根据不同的pointstate来画对应的颜色
			if (Maze[i][j].getpointstate() == point::State::wall)
			{
				scene->setBrush(Qt::black);
			}
			else if (Maze[i][j].getpointstate() == point::State::maywall)
			{
				scene->setBrush(Qt::gray);
			}
			else if (Maze[i][j].getpointstate() == point::State::path)
			{
				//注意 画path时 多判断一次是否被标记为答案路径 是就红色 不是就保持绿色
				if (Maze[i][j].getkey() == true)
				{
					scene->setBrush(Qt::red);
				}
				else if (Maze[i][j].getkey() == false)
				{
					scene->setBrush(Qt::green);
				}
			}
			else if (Maze[i][j].getpointstate() == point::State::maypath)
			{
				scene->setBrush(Qt::yellow);
			}
			else if (Maze[i][j].getpointstate() == point::State::start)
			{
				scene->setBrush(Qt::red);
			}
			else if (Maze[i][j].getpointstate() == point::State::end)
			{
				scene->setBrush(Qt::red);
			}
			else if (Maze[i][j].getpointstate() == point::State::food)
			{
				scene->setBrush(Qt::white);
			}
			else if (Maze[i][j].getpointstate() == point::State::trap)
			{
				scene->setBrush(Qt::yellow);
			}
			else if (Maze[i][j].getpointstate() == point::State::player)
			{
				scene->setBrush(Qt::blue);
			}

			scene->setPen(pen);//让格子线消失
			gameBoard->addItem(scene);
			items[i].push_back(scene);
			py += maze->getmaxcol();
		}
		px += maze->getmaxrow();
		py = 0;
	}
	ui.graphicsView->update();//更新重绘
}