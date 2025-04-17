#include "signuppage.h"
#include "ui_signuppage.h"
#include <QMessageBox>

signUpPage::signUpPage(database* db,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::signUpPage)
    , dbObj(db)
{
    ui->setupUi(this);
    connect(ui->submitBtn, &QPushButton::clicked, this, &signUpPage::onSubmitBtnClicked);
    connect(ui->backtoLogInBtn, &QPushButton::clicked, this, &signUpPage::onBackToLognInBtnClicked);
}

signUpPage::~signUpPage()
{
    delete ui;
}


void signUpPage::onSubmitBtnClicked()
{
    QString username = ui->userlineEdit->text();
    QString tempPass = ui->createPasslineEdit->text();
    QString confirmPass = ui->confirmPasslineEdit->text();

    if(username.isEmpty() || tempPass.isEmpty() || confirmPass.isEmpty())
    {
        QMessageBox::warning(this, "Sign Up Error", "Field is Empty");
        return;
    }

    if(dbObj->userExists(username)) {
        QMessageBox::warning(this, "Error", "Username already exists");
        return;
    }

    if(confirmPass != tempPass)
        QMessageBox::warning(this, "Password Error", "Passwords dont match");
    else
    {
        dbObj->insertUser(username,confirmPass);
        QMessageBox::information(this, "Success", "Registration completed");
        ui->userlineEdit->clear();
        ui->createPasslineEdit->clear();
        ui->confirmPasslineEdit->clear();
    }
}

void signUpPage::onBackToLognInBtnClicked()
{
    a = "jk";
    b = "tp";
    emit notifyBtn(a,b);
}

void signUpPage::closeEvent(QCloseEvent *event)
{
    qApp->quit();
    event->accept();
}
