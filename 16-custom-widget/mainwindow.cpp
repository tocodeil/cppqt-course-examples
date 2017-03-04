#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->c1, &Clicker::clicksChanged,
                     this, &MainWindow::handlePointsChanged);
    QObject::connect(ui->c2, &Clicker::clicksChanged,
                     this, &MainWindow::handlePointsChanged);
    QObject::connect(ui->c3, &Clicker::clicksChanged,
                     this, &MainWindow::handlePointsChanged);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handlePointsChanged(int totalPoints)
{
    if (totalPoints % 10 == 0)
    {
        setStyleSheet("background: lightgreen");
    }
    else
    {
        setStyleSheet("background: none");
    }
}
