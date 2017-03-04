#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSettings s;
    QRect lastPosition = s.value("window/pos", geometry()).toRect();
    setGeometry(lastPosition);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    Q_UNUSED(e);
    QSettings s;
    s.setValue("window/pos", geometry());
}
