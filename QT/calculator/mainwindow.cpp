#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->addBtn, &QPushButton::clicked, this, &MainWindow::onAddBtnClicked);
    connect(ui->subBtn, &QPushButton::clicked, this, &MainWindow::onSubtractBtnClicked);
    connect(ui->multiplyBtn, &QPushButton::clicked, this, &MainWindow::onMuliplyBtnClicked);
    connect(ui->divideBtn, &QPushButton::clicked, this, &MainWindow::onDivideBtnClicked);
    connect(ui->equalBtn, &QPushButton::clicked, this, &MainWindow::onEqualBtnClicked);
    connect(ui->clearBtn, &QPushButton::clicked, this, &MainWindow::onClearBtnClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAddBtnClicked()
{
    num1 = ui->resultBox->text().toDouble();
    operation = "+";
    ui->resultBox->clear();
}

void MainWindow::onSubtractBtnClicked()
{
    num1 = ui->resultBox->text().toDouble();
    operation = "-";
    ui->resultBox->clear();
}

void MainWindow::onMuliplyBtnClicked()
{
    num1 = ui->resultBox->text().toDouble();
    operation = "*";
    ui->resultBox->clear();
}

void MainWindow::onDivideBtnClicked()
{
    num1 = ui->resultBox->text().toDouble();
    operation = "/";
    ui->resultBox->clear();
}

void MainWindow::onEqualBtnClicked()
{
    num2 = ui->resultBox->text().toDouble();
    if(operation == "+")
        result = num1 + num2;
    if(operation == "-")
        result = num1 - num2;
    if(operation == "*")
        result = num1 * num2;
    if(operation == "/")
        result = num1 / num2;

    ui->resultBox->setText(QString::number(result));
    qDebug() << num1 << operation << num2 << " = " << result;
}

void MainWindow::onClearBtnClicked()
{
    num1 = 0.0;
    num2 = 0.0;
    ui->resultBox->clear();
}

