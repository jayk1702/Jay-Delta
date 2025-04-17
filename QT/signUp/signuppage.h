#ifndef SIGNUPPAGE_H
#define SIGNUPPAGE_H

#include "database.h"
#include <QDialog>
#include <QCloseEvent>
#include <QApplication>

namespace Ui {
class signUpPage;
}

class signUpPage : public QDialog
{
    Q_OBJECT

public:
    explicit signUpPage(database *db,QWidget *parent = nullptr);
    ~signUpPage();
    QString a,b;

public slots:

    void onSubmitBtnClicked();
    void onBackToLognInBtnClicked();


private:
    Ui::signUpPage *ui;
    database *dbObj;

    void connectToDatabase();
    void closeEvent(QCloseEvent *event) override;


signals:
    void notifyBtn(QString,QString);
};

#endif // SIGNUPPAGE_H
