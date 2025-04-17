#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>

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
    void toggleStartStop();
    void resetStopwatch();
    void updateTimer();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QTime time;
    bool running;
};
#endif // MAINWINDOW_H
