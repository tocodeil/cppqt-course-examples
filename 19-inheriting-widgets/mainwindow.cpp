#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->label, &ClickableLabel::clicked,
                     [&]() { ui->label->setText("Ouch!") ;});
}

MainWindow::~MainWindow()
{
    delete ui;
}
