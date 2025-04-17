#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dbObj = new database();
    signUp = new signUpPage(dbObj,this);

    connect(ui->logInBtn, &QPushButton::clicked, this, &MainWindow::onLogInBtnClicked);
    connect(ui->signUpBtn, &QPushButton::clicked, this, &MainWindow::onSignUpBtnClicked);
    connect(signUp, &signUpPage::notifyBtn, this, &MainWindow::onNotifyBtn);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &MainWindow::onCancelBtnClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete signUp;
}


void MainWindow::onLogInBtnClicked()
{
    QString username = ui->enterUsername->text();
    QString password = ui->enterPassword->text();

    if(username.isEmpty() || password.isEmpty())
        QMessageBox::warning(this, "Log In Error", "Please enter both username and password");

    if(!dbObj->userExists(username))
    {
        qDebug() << "User not found";
        QMessageBox::warning(this,"Log In Error", "User not found, please SignUp");
        return;
    }

    if(dbObj->verifyCredentials(username,password))
    {
            qDebug() << "Success";
            QMessageBox::information(this, "Log In", "Log In Successfull");
            ui->enterUsername->clear();
            ui->enterPassword->clear();
    }else
        {
            qDebug() << "Failed";
            QMessageBox::warning(this, "Log In Failed", "Incorrect username or password");
        }
}

void MainWindow::onSignUpBtnClicked()
{
    this->hide();
    signUp->show();
}

void MainWindow::onNotifyBtn(QString a, QString b)
{
    signUp->hide();
    qDebug() << a << " " << b;
    this->show();
}

void MainWindow::onCancelBtnClicked()
{
    qApp->quit();
}

