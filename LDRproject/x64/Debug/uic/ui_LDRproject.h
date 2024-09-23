/********************************************************************************
** Form generated from reading UI file 'LDRproject.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LDRPROJECT_H
#define UI_LDRPROJECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "opengl3dmaze.h"

QT_BEGIN_NAMESPACE

class Ui_LDRprojectClass
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_2;
    QGraphicsView *graphicsView;
    QLineEdit *lineEdit;
    opengl3Dmaze *openGLWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *LDRprojectClass)
    {
        if (LDRprojectClass->objectName().isEmpty())
            LDRprojectClass->setObjectName("LDRprojectClass");
        LDRprojectClass->resize(721, 869);
        centralWidget = new QWidget(LDRprojectClass);
        centralWidget->setObjectName("centralWidget");
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(20, 200, 161, 131));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName("pushButton");

        verticalLayout->addWidget(pushButton);

        pushButton_3 = new QPushButton(layoutWidget);
        pushButton_3->setObjectName("pushButton_3");

        verticalLayout->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(layoutWidget);
        pushButton_4->setObjectName("pushButton_4");

        verticalLayout->addWidget(pushButton_4);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName("pushButton_2");
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(pushButton_2);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(3, 1);
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setGeometry(QRect(200, 10, 381, 341));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(10, 20, 171, 161));
        openGLWidget = new opengl3Dmaze(centralWidget);
        openGLWidget->setObjectName("openGLWidget");
        openGLWidget->setGeometry(QRect(110, 360, 281, 191));
        LDRprojectClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LDRprojectClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 721, 21));
        LDRprojectClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(LDRprojectClass);
        mainToolBar->setObjectName("mainToolBar");
        LDRprojectClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(LDRprojectClass);
        statusBar->setObjectName("statusBar");
        LDRprojectClass->setStatusBar(statusBar);

        retranslateUi(LDRprojectClass);

        QMetaObject::connectSlotsByName(LDRprojectClass);
    } // setupUi

    void retranslateUi(QMainWindow *LDRprojectClass)
    {
        LDRprojectClass->setWindowTitle(QCoreApplication::translate("LDRprojectClass", "LDRproject", nullptr));
        pushButton->setText(QCoreApplication::translate("LDRprojectClass", "\347\241\256\350\256\244", nullptr));
        pushButton_3->setText(QCoreApplication::translate("LDRprojectClass", "\347\255\224\346\241\210", nullptr));
        pushButton_4->setText(QCoreApplication::translate("LDRprojectClass", "\346\223\246\351\231\244\347\255\224\346\241\210", nullptr));
        pushButton_2->setText(QCoreApplication::translate("LDRprojectClass", "\351\207\215\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LDRprojectClass: public Ui_LDRprojectClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LDRPROJECT_H
