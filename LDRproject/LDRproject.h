#pragma once
#include <QtWidgets/QMainWindow>
#include <QOpenGLWidget>
#include<QObject>
#include "ui_LDRproject.h"
#include "mazedata.h"
#include <QOpenGLWidget>
#include <GL/glut.h>
#include <math.h>
#include<iostream>
#include<time.h>
#include "mazedata.h"
#include <QOpenGLFunctions_3_3_Core>

class LDRproject : public QMainWindow//基类为QMainWindow
{
	Q_OBJECT//qt写法

public:
	LDRproject(QWidget* parent = nullptr);//构造
	~LDRproject();//析构

private slots://qt槽函数 界面上做出操作调用操作对应组件的函数
	void on_pushButton_2_clicked();//点击重置后执行的的程序
	void on_pushButton_3_clicked();//点击答案后执行的的程序
	void on_pushButton_4_clicked();//点击擦除答案后执行的的程序
	void on_lineEdit_editingFinished();//点击确定或者输入框输入字符后按回车执行的的程序
private:
	Ui::LDRprojectClass ui;

	QGraphicsScene* gameBoard = nullptr;
	void drawmap();

	QVector<QVector<QGraphicsRectItem*>> items;

	mazedata* maze = nullptr;//私有变量mazedata*

	std::string lastProcessedText = "";//记录上一次输入框输入到哪里
	std::string currentText = "";//记录输入框输入到哪里 输入框会返回所有字符 但我要每次只读新输入的不看之前输入的
	bool button3run = false;//记录答案按钮是否被按 不清空向量/栈 连按两次 向量/栈可能出错

public:
	void getmazedata(mazedata* MAZE) { maze = MAZE; };//私有变量mazedata*指向open3Dmaze的mazedata实例私有变量
	void run();//运行功能
};
