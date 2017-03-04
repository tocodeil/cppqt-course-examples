#include <QCoreApplication>
#include <QtNetwork>
#include "../common/message.h"
#include <QtCore>

Message readNextMessage(QTcpSocket *socket)
{
    QDataStream ds(socket);
    Message res;
    ds.startTransaction();
    ds >> res;
    if (ds.commitTransaction())
    {
        return res;
    }
    else
    {
        return Message();
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTcpServer server;
    QHash<QTcpSocket *, QString> m_connectedClients;

    if (!server.listen(QHostAddress::Any, 3030))
    {
        qDebug() << "Error: " << server.errorString();
        return 1;
    }

    QObject::connect(&server, &QTcpServer::newConnection,
                     [&server, &m_connectedClients] {
        while (server.hasPendingConnections())
        {
            QTcpSocket *socket = server.nextPendingConnection();
            m_connectedClients.insert(socket, "Guest");

            QObject::connect(socket, &QTcpSocket::disconnected,
                             [socket, &m_connectedClients] {
                m_connectedClients.remove(socket);
                socket->deleteLater();
            });

            QObject::connect(socket, &QTcpSocket::readyRead,
                             [socket, &m_connectedClients] {
                Message msg = readNextMessage(socket);
                if (msg.type == ESetUserName)
                {
                    m_connectedClients.insert(socket, msg.data.toString());
                }
                else if (msg.type == EGetUsers)
                {
                    QDataStream ds(socket);
                    Message userList;
                    userList.type = EUserList;
                    userList.data = QVariant::fromValue<QStringList>(m_connectedClients.values());
                    ds << userList;
                }
                else if (msg.type == EBroadcastMessage)
                {
                    QString fromName = m_connectedClients.value(socket);
                    msg.data = QString("[%1] %2").arg(fromName).arg(msg.data.toString());

                    for (auto s : m_connectedClients.keys())
                    {
                        QDataStream ds(s);
                        ds << msg;
                    }
                }
            });
        }
    });

    return a.exec();
}
