#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::onActionNew);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::onActionOpen);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::onActionSave);
    connect(ui->actionSave_As, &QAction::triggered, this, &MainWindow::onActionSaveAs);
    connect(ui->actionCut, &QAction::triggered, this, &MainWindow::onActionCut);
    connect(ui->actionCopy, &QAction::triggered, this, &MainWindow::onActionCopy);
    connect(ui->actionPaste, &QAction::triggered, this, &MainWindow::onActionPaste);
    connect(ui->actionRedo, &QAction::triggered, this, &MainWindow::onActionRedo);
    connect(ui->actionUndo, &QAction::triggered, this, &MainWindow::onActionUndo);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onActionNew()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}

void MainWindow::onActionOpen()
{
    QString file = QFileDialog::getOpenFileName(this, "Open FIle");

    QFile filename(file);
    currentFile = file;

    if(!filename.open(QIODevice::ReadOnly, QFile::Text))
    {
        QMessageBox::warning(this, "Error", "Can't open file");
        return;
    }
    QTextStream in(&filename);
    QString text = in.readAll();

    ui->textEdit->setText(text);

    filename.close();
}

void MainWindow::onActionSave()
{
    // QString file = QFileDialog::getSaveFileName(this, "Save File");

    QFile filename(currentFile);


    if(!filename.open(QFile::WriteOnly, QFile::Text))
    {
        QMessageBox::warning(this, "Error", "Can't save file" + filename.errorString());
        return;
    }

    QTextStream out(&filename);

    QString text = ui->textEdit->toPlainText();

    out << text;

    filename.flush();
    filename.close();
}

void MainWindow::onActionSaveAs()
{
    QString file = QFileDialog::getSaveFileName(this, "Save File");

    // Debugging output: Check the returned file path
    qDebug() << "Selected file: " << file;

    // Ensure the file has an extension if not provided
    if (!file.endsWith(".txt", Qt::CaseInsensitive)) {
        file.append(".txt");  // Add .txt if not specified
    }

    if (file.isEmpty()) {
        return;  // User canceled, no need to proceed
    }

    QFile fileToSave(file);
    currentFile = file;

    // Debugging output: Check the file path for saving
    qDebug() << "Saving to file: " << fileToSave.fileName();


    if(!fileToSave.open(QIODevice::WriteOnly, QIODevice::Text))
    {
        qDebug() << "Error opening file for writing:";
        qDebug() << "Error String: " << fileToSave.errorString();
        qDebug() << "Error Number: " << fileToSave.error();
        QMessageBox::warning(this, "Error", "Can't save file" + fileToSave.errorString());
        return;
    }

    QTextStream out(&fileToSave);

    QString text = ui->textEdit->toPlainText();

    // Debugging output: Check the content being written to the file
    qDebug() << "Text to save: " << text;

    out << text;

    fileToSave.flush();
    fileToSave.close();

    // Debugging output: Check if file was saved successfully
    qDebug() << "File saved successfully!";
}

void MainWindow::onActionCut()
{
    ui->textEdit->cut();
}

void MainWindow::onActionCopy()
{
    ui->textEdit->copy();
}

void MainWindow::onActionPaste()
{
    ui->textEdit->paste();
}

void MainWindow::onActionRedo()
{
    ui->textEdit->redo();
}

void MainWindow::onActionUndo()
{
    ui->textEdit->undo();
}
