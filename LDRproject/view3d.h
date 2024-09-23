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
    mazedata* maze = nullptr;//如main.cpp中所说 mazedata实例在opengl3Dmaze中 其余两个类 这里是view3d 中为指针mazedata*
   
public:
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;
    //以上三个函数是QOpenGLWidget仅有的三个函数 而且不应该随便加参数变成有参函数

    void drawroad(float size);//封装画路
    void drawleftwall(float size);//封装画左手边墙
    void drawrightwall(float size);//封装画右手边墙
    void drawendwall(float size);//封装画路的尽头的墙
    //以上四个均为平面
public:
    ~view3d();
public:
    explicit view3d(QWidget* parent = nullptr);
 
    void getmazedata(mazedata* MAZE) { maze = MAZE; };//数据传递 接取地址给指针
};
