#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->btnSearch, &QPushButton::clicked,
                     this, &MainWindow::search);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::search()
{
    ui->result->setText(tr("No flights found"));
}
