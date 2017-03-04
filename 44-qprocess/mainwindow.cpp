#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QDebug>
#include <QErrorMessage>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    proc = new QProcess(this);
    errorDialog = new QErrorMessage(this);

    QObject::connect(ui->btnRefresh, &QPushButton::clicked,
                     this, &MainWindow::handleRefresh);
    QObject::connect(proc, &QProcess::readyRead,
                     this, &MainWindow::handleReadyRead);
    QObject::connect(proc, static_cast<void (QProcess::*)(int)>(&QProcess::finished),
                     this, &MainWindow::handleProcessFinished);
    QObject::connect(proc, &QProcess::errorOccurred,
                     this, &MainWindow::handleError);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleRefresh()
{
    if ((proc->state() == QProcess::Starting) || proc->state() == QProcess::Running)
    {
        // if clicked while running
        proc->kill();
    }
    proc->start("/sbin/ifconfig");
    ui->listIf->clear();
    ui->btnRefresh->setEnabled(false);
}

void MainWindow::handleReadyRead()
{
    QRegExp interfaceLine("^([a-z0-9]+):");
    while (proc->canReadLine())
    {
        QString line = proc->readLine();
        if (line.contains(interfaceLine))
        {
            QString name = interfaceLine.cap(1);
            ui->listIf->addItem(name);
        }
    }
}

void MainWindow::handleProcessFinished()
{
    ui->btnRefresh->setEnabled(true);
}

void MainWindow::handleError(QProcess::ProcessError error)
{
    qDebug() << "Error " << error;
    errorDialog->showMessage(QString("Error [%1]: %2").arg(error).arg(proc->errorString()));
}
