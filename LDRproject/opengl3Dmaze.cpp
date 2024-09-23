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
	// ���� OpenGL �ӿڵĴ���
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void opengl3Dmaze::paintGL()
{
	vector<vector<point>> Maze = maze.getmaze();
	//���������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//����ͶӰ����
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, width(), height(), 0.0, -200.0, 200.0); // ��������ͶӰ����

	// ������ͼ����
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(50.0f, 20.0f, -50.0f,   // �����λ�ã��������̧��һЩ��Զ���Թ�
		50.0f, -10.0f, 0.0f,     // Ŀ��λ�ã�ָ���Թ�������
		0.0f, 1.0f, 0.0f);


	// �����Թ�
	for (int row = 0; row < maze.getmaxrow(); ++row) {
		for (int col = 0; col < maze.getmaxcol(); ++col) {
			if (Maze[row][col].getpointstate() == point::State::wall || Maze[row][col].getpointstate() == point::State::maywall) {
				// ����ǽ�岿��
				glPushMatrix();
				glTranslatef(-col * 10.0f, row * 10.0f, 0.0f);
				glColor3f(0.0f, 0.0f, 0.0f); // ����ǽ����ɫ
				drawCube(10.0f); // ����������
				glColor3f(1.0f, 0.9f, 0.8f);
				drawwalllines(10.0f);
				glPopMatrix();
			}
			else if (Maze[row][col].getpointstate() == point::State::start || Maze[row][col].getpointstate() == point::State::end) {
				// ����·������
				glPushMatrix();
				glTranslatef(-col * 10.0f, row * 10.0f, 0.0f);
				glColor3f(1.0f, 0.0f, 0.0f); // ����·����ɫ
				//drawCube(10.0f); // ����������
				drawroad(10.0f);
				glColor3f(0.0f, 0.0f, 0.0f);
				//drawpathlines(10.0f);
				glPopMatrix();
			}
			else if (Maze[row][col].getpointstate() == point::State::path) {
				// ����·������
				glPushMatrix();
				glTranslatef(-col * 10.0f, row * 10.0f, 0.0f);
				if (Maze[row][col].getkey() == true)
				{
					glColor3f(1.0f, 0.0f, 0.0f); // ����·����ɫ
				}
				else if (Maze[row][col].getkey() == false)
				{
					glColor3f(0.0f, 1.0f, 0.0f); // ����·����ɫ
				}
				//glColor3f(0.0f, 1.0f, 0.0f); // ����·����ɫ
				//drawCube(10.0f); // ����������
				drawroad(10.0f);
				glColor3f(0.0f, 0.0f, 0.0f);
				drawpathlines(10.0f);
				glPopMatrix();
			}
			else if (Maze[row][col].getpointstate() == point::State::food) {
				// ����·������
				glPushMatrix();
				glTranslatef(-col * 10.0f, row * 10.0f, 0.0f);
				glColor3f(1.0f, 1.0f, 1.0f); // ����·����ɫ
				//drawCube(10.0f); // ����������
				drawroad(10.0f);
				glPopMatrix();
			}
			else if (Maze[row][col].getpointstate() == point::State::player) {
				// ����·������
				glPushMatrix();
				glTranslatef(-col * 10.0f, row * 10.0f, 0.0f);
				glColor3f(0.0f, 0.0f, 1.0f); // ����·����ɫ
				drawCube(10.0f); // ����������
				glColor3f(0.0f, 0.0f, 0.0f);
				drawwalllines(10.0f);
				//drawroad(10.0f);
				glPopMatrix();
			}
		}
	}

	// ˢ�»�ͼ
	update();
}

void opengl3Dmaze::drawCube(float size)
{
	float halfSize = size / 2.0f;

	glBegin(GL_QUADS);

	// �����������������
	// ����
	glVertex3f(-halfSize, -halfSize, halfSize);
	glVertex3f(halfSize, -halfSize, halfSize);
	glVertex3f(halfSize, halfSize, halfSize);
	glVertex3f(-halfSize, halfSize, halfSize);

	// ����
	glVertex3f(-halfSize, -halfSize, -halfSize);
	glVertex3f(halfSize, -halfSize, -halfSize);
	glVertex3f(halfSize, halfSize, -halfSize);
	glVertex3f(-halfSize, halfSize, -halfSize);

	// �����ĸ���
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

	// �����������������
	// ����
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

	//// ����ı�

	// ����ı�
	glVertex3f(-halfSize, -halfSize, -halfSize);
	glVertex3f(halfSize, -halfSize, -halfSize);

	glVertex3f(halfSize, -halfSize, -halfSize);
	glVertex3f(halfSize, halfSize, -halfSize);

	glVertex3f(halfSize, halfSize, -halfSize);
	glVertex3f(-halfSize, halfSize, -halfSize);

	glVertex3f(-halfSize, halfSize, -halfSize);
	glVertex3f(-halfSize, -halfSize, -halfSize);

	// ��������ͱ���ı�
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

	// ����ı�
	glVertex3f(-halfSize, halfSize, halfSize);
	glVertex3f(halfSize, -halfSize, halfSize);

	glVertex3f(halfSize, -halfSize, halfSize);
	glVertex3f(-halfSize, halfSize, halfSize);

	glEnd();
	update();
}