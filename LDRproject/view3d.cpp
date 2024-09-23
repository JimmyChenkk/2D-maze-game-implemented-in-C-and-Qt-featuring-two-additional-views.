#include "view3d.h"
#include "opengl3Dmaze.h"
#include <GL/glut.h>
#include <math.h>
#include<iostream>
#include<time.h>
#include "mazedata.h"
#include "LDRproject.h"
#include <QTimer>
using namespace std;


view3d::view3d(QWidget* p) :QOpenGLWidget(p)
{

}

view3d::~view3d()
{

}

void view3d::initializeGL()
{
	initializeOpenGLFunctions();
}

void view3d::resizeGL(int w, int h)
{
	// 调整 OpenGL 视口的代码
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void view3d::paintGL()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // 设置清屏颜色为白色
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0,  // 摄像机位置
		0.0, 0.0, 0.0,  // 观察点位置
		0.0, 1.0, 0.0); // 上方向向量


	int countroad = maze->getCountroad();
	int countleftwall = maze->getCountleftwall();
	int countrightwall = maze->getCountrightwall();
	// 绘制地板
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();


	for (int v = 0; v < countroad; v++)
	{
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, 1.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		drawroad(1.0f);
		glPopMatrix();

	}
	drawendwall(1.0f);
	for (int v = 0; v < countroad; v++)
	{
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, -1.0f);
		glPopMatrix();
	}


	for (int v = 0; v < countleftwall; v++)
	{
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, 1.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		drawleftwall(1.0f);
		glPopMatrix();

	}
	for (int v = 0; v < countleftwall; v++)
	{
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, -1.0f);
		glPopMatrix();
	}


	for (int v = 0; v < countrightwall; v++)
	{
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, 1.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		drawrightwall(1.0f);
		glPopMatrix();

	}
	for (int v = 0; v < countrightwall; v++)
	{
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, -1.0f);
		glPopMatrix();
	}


	update();
}




void view3d::drawroad(float size)
{

	float halfSize = size;
	glBegin(GL_QUADS);


	glVertex3f(-halfSize, -halfSize, -halfSize);
	glVertex3f(-halfSize, -halfSize, halfSize);
	glVertex3f(halfSize, -halfSize, halfSize);
	glVertex3f(halfSize, -halfSize, -halfSize);


	glEnd();
}

void view3d::drawendwall(float size)
{
	glColor3f(0.0f, 0.0f, 1.0f);
	float halfSize = size;
	glBegin(GL_QUADS);

	glVertex3f(-halfSize, -halfSize, -halfSize);
	glVertex3f(halfSize, -halfSize, -halfSize);
	glVertex3f(halfSize, halfSize, -halfSize);
	glVertex3f(-halfSize, halfSize, -halfSize);



	glEnd();
}

void view3d::drawleftwall(float size)
{
	glColor3f(0.0f, 0.0f, 1.0f);
	float halfSize = size;
	glBegin(GL_QUADS);

	glVertex3f(-halfSize, -halfSize, -halfSize);
	glVertex3f(-halfSize, -halfSize, halfSize);
	glVertex3f(-halfSize, halfSize, halfSize);
	glVertex3f(-halfSize, halfSize, -halfSize);


	glEnd();
}

void view3d::drawrightwall(float size)
{
	glColor3f(0.0f, 0.0f, 1.0f);
	float halfSize = size;
	glBegin(GL_QUADS);

	glVertex3f(+halfSize, halfSize, halfSize);
	glVertex3f(+halfSize, halfSize, -halfSize);
	glVertex3f(+halfSize, -halfSize, -halfSize);
	glVertex3f(+halfSize, -halfSize, halfSize);


	glEnd();
}
