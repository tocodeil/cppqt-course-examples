#include <QCoreApplication>
#include <QtNetwork>
#include <QProcessEnvironment>
#include <stdexcept>
#include <QtCore>

quint16 getPort() {
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    bool ok = false;
    quint16 port = env.value("PORT", "3030").toUInt(&ok);
    if (!ok)
    {
        throw std::invalid_argument(
                    QString("Invalid value for PORT. Expected number but got: %1")
                    .arg(env.value("PORT"))
                    .toStdString());
    }
    return port;
}

int broadcastServer(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTcpServer server;
    quint16 port = getPort();
    QSet<QTcpSocket *> connectedClients;

    QObject::connect(&server, &QTcpServer::newConnection,
                     [&] {
        while (server.hasPendingConnections())
        {
            QTcpSocket *socket = server.nextPendingConnection();
            connectedClients.insert(socket);

            QObject::connect(socket, &QTcpSocket::readyRead,
                             [socket, &server, &connectedClients] {
                auto data = socket->readAll();
                for (auto client : connectedClients)
                {
                    if (client != socket)
                    {
                        client->write("> ");
                        client->write(data);
                    }
                }
            });

            QObject::connect(socket, &QTcpSocket::disconnected,
                             [socket, &connectedClients] {
                connectedClients.remove(socket);
                socket->deleteLater();
            });
        }


    });

    if (!server.listen(QHostAddress::LocalHost, port)) return 2;
    qDebug() << "Listening on port: " << port;

    return a.exec();
}


int echoServer(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTcpServer server;
    quint16 port = getPort();

    QObject::connect(&server, &QTcpServer::newConnection,
                     [&] {
        while (server.hasPendingConnections())
        {
            QTcpSocket *socket = server.nextPendingConnection();

            QObject::connect(socket, &QTcpSocket::readyRead,
                             [socket] {
                socket->write(socket->readAll());
            });

            QObject::connect(socket, &QTcpSocket::disconnected,
                             [socket] {
                 socket->deleteLater();
            });
        }

    });

    if (!server.listen(QHostAddress::LocalHost, port)) return 2;
    qDebug() << "Listening on port: " << port;

    return a.exec();
}

int helloWorldServer(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    quint16 port = getPort();

    QTcpServer server;

    QObject::connect(&server, &QTcpServer::newConnection,
                     [&] {
        while (server.hasPendingConnections())
        {
            QTcpSocket *socket = server.nextPendingConnection();
            socket->write("Hello World!\n");
            socket->close();

            QObject::connect(socket, &QTcpSocket::disconnected,
                             [socket] { socket->deleteLater(); });
        }
    });

    if (server.listen(QHostAddress::LocalHost, port))
    {
        qDebug() << "Listening on port: " << port;
        return a.exec();
    }
    else
    {
        qDebug() << "Listen failed: " << server.errorString();
    }
    return 1;
}

int main(int argc, char *argv[])
{
    return echoServer(argc, argv);
}
