#include "LDRproject.h"
#include "opengl3Dmaze.h"
#include "view3d.h"
#include <QtWidgets/QApplication>
#include <QOpenGLWidget>
#include <QWidget>
#include <GL/glut.h>
#include <math.h>
#include<iostream>
#include<time.h>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	//�����������ʵ��
	LDRproject w;//������ ����QMainWindow
	opengl3Dmaze w2(&w);//�趨Ϊ�Ӵ��� ����QOpenGLWidget
	view3d w3(&w);//�趨Ϊ�Ӵ��� ����QOpenGLWidget

	w2.setGeometry(0, 365, 300, 200);//�����Ӵ���λ��
	w3.setGeometry(300, 365, 300, 200);//�����Ӵ���λ��
	w.getmazedata(w2.throwoutmazedata());//mazedata���ʵ����Ϊopengl3Dmaze��˽�б���
	w3.getmazedata(w2.throwoutmazedata());//Ϊ������������ͬ����������LDRproject���Ӵ���view3d�඼��˽�б���mazedata*
	//ͨ������opengl3Dmaze��mazedataʵ����ַ�ӳ��� Ҳ��ͨ�����������������˽�б���mazedataָ���Ϊָ��opengl3Dmaze��mazedataʵ��"maze"

	w.run();//���й���
	w2.update();//����openglwidget����Ļ�ͼ
	w3.update();//����openglwidget����Ļ�ͼ

	w.show();//��ʾ������
	return a.exec();//qt��ѭ��
}
