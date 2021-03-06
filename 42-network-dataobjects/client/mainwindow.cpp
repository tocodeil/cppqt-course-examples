#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>
#include "message.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_socket = new QTcpSocket(this);
    QObject::connect(ui->btnConnect, &QPushButton::clicked,
                     this, &MainWindow::handleConnect);
    QObject::connect(ui->eIp, &QLineEdit::returnPressed,
                     this, &MainWindow::handleConnect);

    QObject::connect(ui->btnSend, &QPushButton::clicked,
                     this, &MainWindow::handleSend);
    QObject::connect(ui->eMessage, &QLineEdit::returnPressed,
                     this, &MainWindow::handleSend);

    QObject::connect(m_socket, &QTcpSocket::connected,
                     this, &MainWindow::handleSocketConnected);
    QObject::connect(m_socket, &QTcpSocket::disconnected,
                     this, &MainWindow::handleSocketDisconnected);
    QObject::connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)),
                     this, SLOT(handleSocketError(QAbstractSocket::SocketError)));
    QObject::connect(m_socket, &QTcpSocket::readyRead,
                     this, &MainWindow::handleReadyRead);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleConnect()
{
    QString serverAddr = ui->eIp->text();
    m_socket->connectToHost(QHostAddress(serverAddr), 3030);
    ui->btnConnect->setEnabled(false);
    ui->eIp->setEnabled(false);
}

void MainWindow::handleSend()
{
    Message msg;
    msg.type = EBroadcastMessage;
    msg.data = ui->eMessage->text();
    QDataStream ds(m_socket);
    ds << msg;

    ui->eMessage->setText("");
}

void MainWindow::handleSocketDisconnected()
{
    ui->log->insertPlainText("[Connection Lost]");
    ui->btnConnect->setEnabled(true);
    ui->eIp->setEnabled(true);
}

void MainWindow::handleSocketConnected()
{
    ui->log->insertPlainText("[Connection Ready]");
    ui->eMessage->setEnabled(true);
    ui->btnSend->setEnabled(true);

    Message msg;
    msg.type = ESetUserName;
    msg.data = ui->eName->text();
    QDataStream ds(m_socket);
    ds << msg;
}

void MainWindow::handleSocketError(QAbstractSocket::SocketError socketError)
{
    ui->log->insertPlainText(QString("[Connection Error] %1").arg(socketError));
    ui->btnConnect->setEnabled(true);
    ui->eIp->setEnabled(true);
}

void MainWindow::handleReadyRead()
{
    qDebug() << "ready read";
    Message msg;
    QDataStream ds(m_socket);
    ds.startTransaction();
    ds >> msg;
    if (ds.commitTransaction())
    {
        if (msg.type == EBroadcastMessage)
        {
            ui->log->append(msg.data.toString());
        }
        else
        {
            qDebug() << "Got: " << msg;
        }
    }
}
