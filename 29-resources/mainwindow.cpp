#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFile f(":/story.txt");
    if (f.open(QIODevice::ReadOnly))
    {
        QTextStream in(&f);
        ui->textEdit->setText(in.readAll());
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
