#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->newFileAction, SIGNAL(triggered()), this, SLOT(newFileSlot()));
    QObject::connect(ui->openFileAction,SIGNAL(triggered()), this, SLOT(openFileSlot()));
    QObject::connect(ui->saveFileAction, SIGNAL(triggered()), this, SLOT(saveFileSlot()));
    QObject::connect(ui->altSaveAction, SIGNAL(triggered()), this, SLOT(altSaveSlot()));
    QObject::connect(ui->quitAction, SIGNAL(triggered()), this, SLOT(close()));
    QObject::connect(ui->cutAction, SIGNAL(triggered()), ui->textEdit, SLOT(cut()));
    QObject::connect(ui->copyAction, SIGNAL(triggered()), ui->textEdit, SLOT(copy()));
    QObject::connect(ui->allSelectAction, SIGNAL(triggered()), ui->textEdit, SLOT(selectAll()));
    QObject::connect(ui->pasteAction,SIGNAL(triggered()),ui->textEdit,SLOT(paste()));
    QObject::connect(ui->undoAction,SIGNAL(triggered()),ui->textEdit,SLOT(undo()));
    QObject::connect(ui->redoAction,SIGNAL(triggered()),ui->textEdit,SLOT(redo()));
//    QObject::connect(ui->fontAction,SIGNAL(triggered()),ui->textEdit,SLOT(redo()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newFileSlot()
{
    if(ui->textEdit->document()->isModified())
    {
        qDebug()<<"File is modified!";
    }
    else{
        qDebug()<<"File is NOT modified!";
        this->setWindowTitle("Untitled.txt");
    }
}

void MainWindow::saveFileSlot()
{
    if(saveFileName.isEmpty())
    {
        this->altSaveSlot();
    }
    else
    {
        QFile *file = new QFile();
        file->setFileName(saveFileName);
        bool ok = file->open(QIODevice::WriteOnly);
        if(ok)
        {
            QTextStream out(file);
            out<<ui->textEdit->toPlainText();
            file->close();
            delete file;
        }
        else
        {
            QMessageBox::information(this, "Error", "File saves open"+file->errorString());
            return ;
        }
    }
}

void MainWindow::altSaveSlot()
{
    saveFileName = QFileDialog::getSaveFileName(this, tr("Save File"), "C:\\Users\\admin\\Desktop");
    if(saveFileName.isEmpty())
    {
        QMessageBox::information(this, "Error", "File must be named!");
    }
    else
    {
        QFile *file = new QFile();
        file->setFileName(saveFileName);
        bool ok = file->open(QIODevice::WriteOnly);
        if(ok)
        {
            QTextStream out(file);
            out<<ui->textEdit->toPlainText();
            file->close();
            delete file;
        }
        else
        {
            QMessageBox::information(this, "Error", "File saves open"+file->errorString());
            return ;
        }
    }

}

void MainWindow::openFileSlot()
{
//    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "C:\\Users\\admin\\Desktop");

    qDebug()<<fileName;
    if(fileName.isEmpty())
    {
        QMessageBox::information(this, "Error", "No such file!");
    }
    else
    {
        QFile *file = new QFile();
        file->setFileName(fileName);
        bool ok = file->open(QIODevice::ReadOnly);
        if(ok)
        {
            QTextStream in(file);
            ui->textEdit->setText(in.readAll());
            file->close();
            delete file;
        }
        else
        {
            QMessageBox::information(this, "Error", "File fail open"+file->errorString());
            return ;
        }
    }
}



