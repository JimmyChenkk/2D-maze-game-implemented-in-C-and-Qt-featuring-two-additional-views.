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
	//创建三个类的实例
	LDRproject w;//主窗口 基类QMainWindow
	opengl3Dmaze w2(&w);//设定为子窗口 基类QOpenGLWidget
	view3d w3(&w);//设定为子窗口 基类QOpenGLWidget

	w2.setGeometry(0, 365, 300, 200);//设置子窗口位置
	w3.setGeometry(300, 365, 300, 200);//设置子窗口位置
	w.getmazedata(w2.throwoutmazedata());//mazedata类的实例作为opengl3Dmaze的私有变量
	w3.getmazedata(w2.throwoutmazedata());//为了三窗口数据同步，主窗口LDRproject和子窗口view3d类都有私有变量mazedata*
	//通过函数opengl3Dmaze把mazedata实例地址扔出来 也是通过函数其余两个类把私有变量mazedata指针改为指向opengl3Dmaze的mazedata实例"maze"

	w.run();//运行功能
	w2.update();//更新openglwidget组件的绘图
	w3.update();//更新openglwidget组件的绘图

	w.show();//显示主窗口
	return a.exec();//qt的循环
}
