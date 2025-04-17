#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    // void onOperationBtnsClicked();
    void onAddBtnClicked();
    void onSubtractBtnClicked();
    void onMuliplyBtnClicked();
    void onDivideBtnClicked();
    void onEqualBtnClicked();
    void onClearBtnClicked();

private:
    Ui::MainWindow *ui;
    double num1 = 0.0;
    double num2 = 0.0;
    QString operation;
    double result;

};
#endif // MAINWINDOW_H
