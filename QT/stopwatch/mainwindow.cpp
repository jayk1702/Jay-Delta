#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , running(false)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    time = QTime(0, 0, 0, 0);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTimer);
    connect(ui->startstopBtn, &QPushButton::clicked, this, &MainWindow::toggleStartStop);
    connect(ui->resetBtn, &QPushButton::clicked, this, &MainWindow::resetStopwatch);
    ui->stopwatchDisplay->setText("00 : 00 : 00 : 00");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTimer()
{
    time = time.addMSecs(10);
    ui->stopwatchDisplay->setText(time.toString("hh : mm : ss : zzz"));
}

void MainWindow::toggleStartStop()
{
    if(running)
    {
        timer->stop();
        ui->startstopBtn->setText("Start");
    }else
    {
        timer->start();
        ui->startstopBtn->setText("Stop");
    }
    running = !running;
}

void MainWindow::resetStopwatch()
{
    timer->stop();
    time = QTime(0, 0, 0, 0);
    ui->stopwatchDisplay->setText("00 : 00 : 00 : 00");
    ui->startstopBtn->setText("Start");
}
