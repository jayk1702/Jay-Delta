/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
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
    QLineEdit *stopwatchDisplay;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *startstopBtn;
    QPushButton *resetBtn;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_2;
    QLCDNumber *hoursLcdNumber;
    QLCDNumber *minutesLcdNumber;
    QLCDNumber *secondsLcdNumber;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        stopwatchDisplay = new QLineEdit(centralwidget);
        stopwatchDisplay->setObjectName("stopwatchDisplay");
        stopwatchDisplay->setGeometry(QRect(310, 140, 201, 51));
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(311, 262, 201, 51));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        startstopBtn = new QPushButton(widget);
        startstopBtn->setObjectName("startstopBtn");

        horizontalLayout->addWidget(startstopBtn);

        resetBtn = new QPushButton(widget);
        resetBtn->setObjectName("resetBtn");

        horizontalLayout->addWidget(resetBtn);

        widget1 = new QWidget(centralwidget);
        widget1->setObjectName("widget1");
        widget1->setGeometry(QRect(311, 205, 201, 51));
        horizontalLayout_2 = new QHBoxLayout(widget1);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        hoursLcdNumber = new QLCDNumber(widget1);
        hoursLcdNumber->setObjectName("hoursLcdNumber");

        horizontalLayout_2->addWidget(hoursLcdNumber);

        minutesLcdNumber = new QLCDNumber(widget1);
        minutesLcdNumber->setObjectName("minutesLcdNumber");

        horizontalLayout_2->addWidget(minutesLcdNumber);

        secondsLcdNumber = new QLCDNumber(widget1);
        secondsLcdNumber->setObjectName("secondsLcdNumber");

        horizontalLayout_2->addWidget(secondsLcdNumber);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        startstopBtn->setText(QCoreApplication::translate("MainWindow", "START / STOP", nullptr));
        resetBtn->setText(QCoreApplication::translate("MainWindow", "RESET", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
