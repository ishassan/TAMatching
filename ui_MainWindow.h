/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *btnok;
    QPushButton *btnbrowse;
    QLabel *label;
    QLineEdit *txtpath;
    QLabel *label_2;
    QLineEdit *txtNum;
    QLineEdit *taload;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *tacourses;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(696, 344);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        btnok = new QPushButton(centralwidget);
        btnok->setObjectName(QStringLiteral("btnok"));
        btnok->setGeometry(QRect(490, 150, 171, 71));
        btnbrowse = new QPushButton(centralwidget);
        btnbrowse->setObjectName(QStringLiteral("btnbrowse"));
        btnbrowse->setGeometry(QRect(570, 60, 101, 27));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(70, 30, 160, 17));
        txtpath = new QLineEdit(centralwidget);
        txtpath->setObjectName(QStringLiteral("txtpath"));
        txtpath->setGeometry(QRect(220, 24, 401, 30));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(82, 108, 190, 17));
        txtNum = new QLineEdit(centralwidget);
        txtNum->setObjectName(QStringLiteral("txtNum"));
        txtNum->setGeometry(QRect(360, 101, 80, 30));
        txtNum->setAlignment(Qt::AlignCenter);
        taload = new QLineEdit(centralwidget);
        taload->setObjectName(QStringLiteral("taload"));
        taload->setGeometry(QRect(360, 173, 80, 33));
        taload->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(60, 180, 231, 20));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 250, 321, 20));
        tacourses = new QLineEdit(centralwidget);
        tacourses->setObjectName(QStringLiteral("tacourses"));
        tacourses->setGeometry(QRect(360, 240, 80, 33));
        tacourses->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 696, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        btnok->setText(QApplication::translate("MainWindow", "Generate Schedule", 0));
        btnbrowse->setText(QApplication::translate("MainWindow", "Browse", 0));
        label->setText(QApplication::translate("MainWindow", "Input File Path (.xlsx)", 0));
        txtpath->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "Number of Choices per TA", 0));
        txtNum->setText(QApplication::translate("MainWindow", "5", 0));
        taload->setText(QApplication::translate("MainWindow", "3", 0));
        label_3->setText(QApplication::translate("MainWindow", "Maximum Number of Slots per TA", 0));
        label_4->setText(QApplication::translate("MainWindow", "Maximum Number of Different Courses per TA", 0));
        tacourses->setText(QApplication::translate("MainWindow", "2", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
