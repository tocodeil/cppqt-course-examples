#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractSocket>

class QTcpSocket;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void handleConnect();
    void handleSend();
    void handleSocketDisconnected();
    void handleSocketConnected();
    void handleSocketError(QAbstractSocket::SocketError socketError);
    void handleReadyRead();

private:
    Ui::MainWindow *ui;
    QTcpSocket *m_socket;
};

#endif // MAINWINDOW_H
