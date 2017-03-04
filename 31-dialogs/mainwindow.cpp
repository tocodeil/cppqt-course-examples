#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include "waitdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    modelessWaitDialog = new WaitDialog(this);

    QObject::connect(ui->btnShowQtModal, &QPushButton::clicked,
                     this, &MainWindow::showQtModalDialog);
    QObject::connect(ui->btnShowMyModal, &QPushButton::clicked,
                     this, &MainWindow::showCustomModalDialog);
    QObject::connect(ui->btnShowMyModeless, &QPushButton::clicked,
                     this, &MainWindow::showCustomModelessDialog);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showQtModalDialog()
{
    QColor res = QColorDialog::getColor();
    ui->colorResult->setText(QString(tr("You selected: %1")).arg(res.name()));
}

void MainWindow::showCustomModalDialog()
{
    WaitDialog w;
    auto res = w.exec();
    ui->colorResult->setText(QString(tr("Finished. Result = %1")).arg(res));
}

void MainWindow::showCustomModelessDialog()
{
    modelessWaitDialog->reset();
    modelessWaitDialog->show();
}
