#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QDebug>
#include <QMap>
#include "database.h"
#include "signuppage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:

    void onLogInBtnClicked();
    void onSignUpBtnClicked();
    void onNotifyBtn(QString a, QString b);
    void onCancelBtnClicked();



private:
    Ui::MainWindow *ui;
    database *dbObj;
    signUpPage *signUp;

};
#endif // MAINWINDOW_H
