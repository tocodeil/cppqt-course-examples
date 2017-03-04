#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <functional>
#include <QMouseEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->btnStart, &QPushButton::clicked,
                    std::bind(static_cast<void (QBasicTimer::*)(int, QObject *)>(&QBasicTimer::start), &m_timer, 10, this));

    QObject::connect(ui->btnStop, &QPushButton::clicked,
                    std::bind(&QBasicTimer::stop, &m_timer));

    ui->btnStart->installEventFilter(this);
    ui->btnStop->installEventFilter(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    event->accept();
    m_ticks++;
    ui->label->setText(QString("%1").arg(m_ticks));
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    event->accept();
    m_ticks = 0;
    ui->label->setText(QString("%1").arg(m_ticks));
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    qDebug() << "Got Event from " << watched << ". Event Object: " << event;
    // return true to filter the event out
    // return false to let the event reach its target
    return false;
}

bool MainWindow::event(QEvent *event)
{
    // qDebug() << "Got Event: " << event;
    return QMainWindow::event(event);
}
