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
    mazedata maze;//如main.cpp中所说 mazedata实例在opengl3Dmaze中 其余两个类中为指针mazedata*

public:
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;
    //以上三个函数是QOpenGLWidget仅有的三个函数 而且不应该随便加参数变成有参函数

    void drawCube(float size);//封装画墙 立方体
    void drawroad(float size);//封装画路 平面 四边形
    void drawwalllines(float size);//封装画线 让墙 立方体更清晰
    void drawpathlines(float size);//封装画线 让路更清晰

public:
	~opengl3Dmaze();
public:
    explicit opengl3Dmaze(QWidget* parent = nullptr);

    mazedata* throwoutmazedata() { return &maze; };//数据传递出mazedata实例地址给其余两个类的指针mazedata*
};
