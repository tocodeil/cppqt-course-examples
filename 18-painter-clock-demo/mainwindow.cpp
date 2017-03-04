#include "mainwindow.h"
#include "ui_mainwindow.h"
#define SECONDS * 100

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->c1->setCount(1 SECONDS);
    ui->c2->setCount(60 SECONDS);
    ui->c3->setCount(3600 SECONDS);

    // adjusting c1 colors is performed via its palette
    QPalette redPacman = ui->c1->palette();
    redPacman.setColor(QPalette::Window, Qt::red);
    ui->c1->setPalette(redPacman);

    // adjusting c2 colors is performed via stylesheets, which has the same effect
    ui->c2->setStyleSheet("background: lightblue");

    QObject::connect(ui->btnToggle, &QPushButton::clicked,
                     this, &MainWindow::handleClick);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleClick()
{
    if (isActive)
    {
        ui->btnToggle->setText("Start");
        ui->c1->stop();
        ui->c2->stop();
        ui->c3->stop();
    }
    else
    {
        ui->btnToggle->setText("Stop");
        ui->c1->start();
        ui->c2->start();
        ui->c3->start();
    }
    isActive = !isActive;
}
