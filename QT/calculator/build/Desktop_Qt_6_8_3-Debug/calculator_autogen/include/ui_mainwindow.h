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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *resultBox;
    QPushButton *addBtn;
    QPushButton *subBtn;
    QPushButton *multiplyBtn;
    QPushButton *divideBtn;
    QPushButton *equalBtn;
    QPushButton *clearBtn;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(361, 251);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        resultBox = new QLineEdit(centralwidget);
        resultBox->setObjectName("resultBox");
        resultBox->setGeometry(QRect(0, 40, 351, 111));
        addBtn = new QPushButton(centralwidget);
        addBtn->setObjectName("addBtn");
        addBtn->setGeometry(QRect(0, 160, 51, 41));
        subBtn = new QPushButton(centralwidget);
        subBtn->setObjectName("subBtn");
        subBtn->setGeometry(QRect(60, 160, 51, 41));
        multiplyBtn = new QPushButton(centralwidget);
        multiplyBtn->setObjectName("multiplyBtn");
        multiplyBtn->setGeometry(QRect(120, 160, 51, 41));
        divideBtn = new QPushButton(centralwidget);
        divideBtn->setObjectName("divideBtn");
        divideBtn->setGeometry(QRect(180, 160, 51, 41));
        equalBtn = new QPushButton(centralwidget);
        equalBtn->setObjectName("equalBtn");
        equalBtn->setGeometry(QRect(240, 160, 51, 41));
        clearBtn = new QPushButton(centralwidget);
        clearBtn->setObjectName("clearBtn");
        clearBtn->setGeometry(QRect(300, 160, 51, 41));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        addBtn->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        subBtn->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        multiplyBtn->setText(QCoreApplication::translate("MainWindow", "*", nullptr));
        divideBtn->setText(QCoreApplication::translate("MainWindow", "/", nullptr));
        equalBtn->setText(QCoreApplication::translate("MainWindow", "=", nullptr));
        clearBtn->setText(QCoreApplication::translate("MainWindow", "C", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
