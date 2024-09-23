#pragma once
#include <QOpenGLWidget>
#include <GL/glut.h>
#include <math.h>
#include<iostream>
#include<time.h>
#include "mazedata.h"
#include <QOpenGLFunctions_3_3_Core>

using namespace std;

class opengl3Dmaze:public QOpenGLWidget ,QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

private:
    mazedata maze;//��main.cpp����˵ mazedataʵ����opengl3Dmaze�� ������������Ϊָ��mazedata*

public:
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;
    //��������������QOpenGLWidget���е��������� ���Ҳ�Ӧ�����Ӳ�������вκ���

    void drawCube(float size);//��װ��ǽ ������
    void drawroad(float size);//��װ��· ƽ�� �ı���
    void drawwalllines(float size);//��װ���� ��ǽ �����������
    void drawpathlines(float size);//��װ���� ��·������

public:
	~opengl3Dmaze();
public:
    explicit opengl3Dmaze(QWidget* parent = nullptr);

    mazedata* throwoutmazedata() { return &maze; };//���ݴ��ݳ�mazedataʵ����ַ�������������ָ��mazedata*
};
