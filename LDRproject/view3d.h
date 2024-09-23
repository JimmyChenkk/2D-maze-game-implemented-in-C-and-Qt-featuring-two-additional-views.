#pragma once
#include <QOpenGLWidget>
#include <GL/glut.h>
#include <math.h>
#include<iostream>
#include<time.h>
#include "mazedata.h"
#include <QOpenGLFunctions_3_3_Core>

using namespace std;

class view3d :public QOpenGLWidget, QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

private:
    mazedata* maze = nullptr;//��main.cpp����˵ mazedataʵ����opengl3Dmaze�� ���������� ������view3d ��Ϊָ��mazedata*
   
public:
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;
    //��������������QOpenGLWidget���е��������� ���Ҳ�Ӧ�����Ӳ�������вκ���

    void drawroad(float size);//��װ��·
    void drawleftwall(float size);//��װ�����ֱ�ǽ
    void drawrightwall(float size);//��װ�����ֱ�ǽ
    void drawendwall(float size);//��װ��·�ľ�ͷ��ǽ
    //�����ĸ���Ϊƽ��
public:
    ~view3d();
public:
    explicit view3d(QWidget* parent = nullptr);
 
    void getmazedata(mazedata* MAZE) { maze = MAZE; };//���ݴ��� ��ȡ��ַ��ָ��
};
