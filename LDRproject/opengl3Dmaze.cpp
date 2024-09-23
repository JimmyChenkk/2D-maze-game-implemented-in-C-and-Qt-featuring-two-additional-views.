#include "opengl3Dmaze.h"
#include <GL/glut.h>
#include <math.h>
#include<iostream>
#include<time.h>
#include "mazedata.h"
#include "LDRproject.h"
#include <QTimer>
using namespace std;


opengl3Dmaze::opengl3Dmaze(QWidget* p) :QOpenGLWidget(p)
{

}

opengl3Dmaze::~opengl3Dmaze()
{

}

void opengl3Dmaze::initializeGL()
{
	initializeOpenGLFunctions();
}

void opengl3Dmaze::resizeGL(int w, int h)
{
	// 调整 OpenGL 视口的代码
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void opengl3Dmaze::paintGL()
{
	vector<vector<point>> Maze = maze.getmaze();
	//清除缓冲区
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//设置投影矩阵
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, width(), height(), 0.0, -200.0, 200.0); // 设置正交投影矩阵

	// 设置视图矩阵
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(50.0f, 20.0f, -50.0f,   // 摄像机位置，将摄像机抬高一些，远离迷宫
		50.0f, -10.0f, 0.0f,     // 目标位置，指向迷宫的中心
		0.0f, 1.0f, 0.0f);


	// 绘制迷宫
	for (int row = 0; row < maze.getmaxrow(); ++row) {
		for (int col = 0; col < maze.getmaxcol(); ++col) {
			if (Maze[row][col].getpointstate() == point::State::wall || Maze[row][col].getpointstate() == point::State::maywall) {
				// 绘制墙体部分
				glPushMatrix();
				glTranslatef(-col * 10.0f, row * 10.0f, 0.0f);
				glColor3f(0.0f, 0.0f, 0.0f); // 设置墙体颜色
				drawCube(10.0f); // 绘制立方体
				glColor3f(1.0f, 0.9f, 0.8f);
				drawwalllines(10.0f);
				glPopMatrix();
			}
			else if (Maze[row][col].getpointstate() == point::State::start || Maze[row][col].getpointstate() == point::State::end) {
				// 绘制路径部分
				glPushMatrix();
				glTranslatef(-col * 10.0f, row * 10.0f, 0.0f);
				glColor3f(1.0f, 0.0f, 0.0f); // 设置路径颜色
				//drawCube(10.0f); // 绘制立方体
				drawroad(10.0f);
				glColor3f(0.0f, 0.0f, 0.0f);
				//drawpathlines(10.0f);
				glPopMatrix();
			}
			else if (Maze[row][col].getpointstate() == point::State::path) {
				// 绘制路径部分
				glPushMatrix();
				glTranslatef(-col * 10.0f, row * 10.0f, 0.0f);
				if (Maze[row][col].getkey() == true)
				{
					glColor3f(1.0f, 0.0f, 0.0f); // 设置路径颜色
				}
				else if (Maze[row][col].getkey() == false)
				{
					glColor3f(0.0f, 1.0f, 0.0f); // 设置路径颜色
				}
				//glColor3f(0.0f, 1.0f, 0.0f); // 设置路径颜色
				//drawCube(10.0f); // 绘制立方体
				drawroad(10.0f);
				glColor3f(0.0f, 0.0f, 0.0f);
				drawpathlines(10.0f);
				glPopMatrix();
			}
			else if (Maze[row][col].getpointstate() == point::State::food) {
				// 绘制路径部分
				glPushMatrix();
				glTranslatef(-col * 10.0f, row * 10.0f, 0.0f);
				glColor3f(1.0f, 1.0f, 1.0f); // 设置路径颜色
				//drawCube(10.0f); // 绘制立方体
				drawroad(10.0f);
				glPopMatrix();
			}
			else if (Maze[row][col].getpointstate() == point::State::player) {
				// 绘制路径部分
				glPushMatrix();
				glTranslatef(-col * 10.0f, row * 10.0f, 0.0f);
				glColor3f(0.0f, 0.0f, 1.0f); // 设置路径颜色
				drawCube(10.0f); // 绘制立方体
				glColor3f(0.0f, 0.0f, 0.0f);
				drawwalllines(10.0f);
				//drawroad(10.0f);
				glPopMatrix();
			}
		}
	}

	// 刷新绘图
	update();
}

void opengl3Dmaze::drawCube(float size)
{
	float halfSize = size / 2.0f;

	glBegin(GL_QUADS);

	// 绘制立方体的六个面
	// 正面
	glVertex3f(-halfSize, -halfSize, halfSize);
	glVertex3f(halfSize, -halfSize, halfSize);
	glVertex3f(halfSize, halfSize, halfSize);
	glVertex3f(-halfSize, halfSize, halfSize);

	// 背面
	glVertex3f(-halfSize, -halfSize, -halfSize);
	glVertex3f(halfSize, -halfSize, -halfSize);
	glVertex3f(halfSize, halfSize, -halfSize);
	glVertex3f(-halfSize, halfSize, -halfSize);

	// 其他四个面
	// ...
	glVertex3f(-halfSize, halfSize, -halfSize);
	glVertex3f(halfSize, halfSize, -halfSize);
	glVertex3f(halfSize, halfSize, halfSize);
	glVertex3f(-halfSize, halfSize, halfSize);

	glVertex3f(-halfSize, -halfSize, -halfSize);
	glVertex3f(halfSize, -halfSize, -halfSize);
	glVertex3f(halfSize, -halfSize, halfSize);
	glVertex3f(-halfSize, -halfSize, halfSize);

	glVertex3f(halfSize, -halfSize, -halfSize);
	glVertex3f(halfSize, halfSize, -halfSize);
	glVertex3f(halfSize, halfSize, halfSize);
	glVertex3f(halfSize, -halfSize, halfSize);

	glVertex3f(-halfSize, -halfSize, -halfSize);
	glVertex3f(-halfSize, halfSize, -halfSize);
	glVertex3f(-halfSize, halfSize, halfSize);
	glVertex3f(-halfSize, -halfSize, halfSize);

	glEnd();
	update();
}

void opengl3Dmaze::drawroad(float size)
{
	float halfSize = size / 2.0f;

	glBegin(GL_QUADS);

	// 绘制立方体的六个面
	// 正面
	/*glVertex3f(-halfSize, -halfSize, halfSize);
	glVertex3f(halfSize, -halfSize, halfSize);
	glVertex3f(halfSize, halfSize, halfSize);
	glVertex3f(-halfSize, halfSize, halfSize);*/


	glVertex3f(-halfSize, -halfSize, halfSize);
	glVertex3f(halfSize, -halfSize, halfSize);
	glVertex3f(halfSize, halfSize, halfSize);
	glVertex3f(-halfSize, halfSize, halfSize);


	glEnd();
	update();
}

void opengl3Dmaze::drawwalllines(float size)
{
	float halfSize = size / 2.0f;

	glBegin(GL_LINES);

	//// 正面的边

	// 背面的边
	glVertex3f(-halfSize, -halfSize, -halfSize);
	glVertex3f(halfSize, -halfSize, -halfSize);

	glVertex3f(halfSize, -halfSize, -halfSize);
	glVertex3f(halfSize, halfSize, -halfSize);

	glVertex3f(halfSize, halfSize, -halfSize);
	glVertex3f(-halfSize, halfSize, -halfSize);

	glVertex3f(-halfSize, halfSize, -halfSize);
	glVertex3f(-halfSize, -halfSize, -halfSize);

	// 连接正面和背面的边
	glVertex3f(-halfSize, -halfSize, halfSize);
	glVertex3f(-halfSize, -halfSize, -halfSize);

	glVertex3f(halfSize, -halfSize, halfSize);
	glVertex3f(halfSize, -halfSize, -halfSize);

	glVertex3f(halfSize, halfSize, halfSize);
	glVertex3f(halfSize, halfSize, -halfSize);

	glVertex3f(-halfSize, halfSize, halfSize);
	glVertex3f(-halfSize, halfSize, -halfSize);

	glEnd();
	update();
}

void opengl3Dmaze::drawpathlines(float size)
{
	float halfSize = size / 2.0f;

	glBegin(GL_LINES);

	// 正面的边
	glVertex3f(-halfSize, halfSize, halfSize);
	glVertex3f(halfSize, -halfSize, halfSize);

	glVertex3f(halfSize, -halfSize, halfSize);
	glVertex3f(-halfSize, halfSize, halfSize);

	glEnd();
	update();
}