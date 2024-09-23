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

class LDRproject : public QMainWindow//����ΪQMainWindow
{
	Q_OBJECT//qtд��

public:
	LDRproject(QWidget* parent = nullptr);//����
	~LDRproject();//����

private slots://qt�ۺ��� �����������������ò�����Ӧ����ĺ���
	void on_pushButton_2_clicked();//������ú�ִ�еĵĳ���
	void on_pushButton_3_clicked();//����𰸺�ִ�еĵĳ���
	void on_pushButton_4_clicked();//��������𰸺�ִ�еĵĳ���
	void on_lineEdit_editingFinished();//���ȷ����������������ַ��󰴻س�ִ�еĵĳ���
private:
	Ui::LDRprojectClass ui;

	QGraphicsScene* gameBoard = nullptr;
	void drawmap();

	QVector<QVector<QGraphicsRectItem*>> items;

	mazedata* maze = nullptr;//˽�б���mazedata*

	std::string lastProcessedText = "";//��¼��һ����������뵽����
	std::string currentText = "";//��¼��������뵽���� �����᷵�������ַ� ����Ҫÿ��ֻ��������Ĳ���֮ǰ�����
	bool button3run = false;//��¼�𰸰�ť�Ƿ񱻰� ���������/ջ �������� ����/ջ���ܳ���

public:
	void getmazedata(mazedata* MAZE) { maze = MAZE; };//˽�б���mazedata*ָ��open3Dmaze��mazedataʵ��˽�б���
	void run();//���й���
};
