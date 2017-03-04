#ifndef MESSAGE_H
#define MESSAGE_H

#include <QDataStream>
#include <QVariant>
#include <QtCore>

enum MessageType {
    ESetUserName,
    EBroadcastMessage,
    EGetUsers,
    EUserList,
    EInvalid,
};

struct Message
{
    MessageType type = EInvalid;
    QVariant data = QVariant();
};


QDataStream &operator<<(QDataStream &stream, const Message &msg);
QDataStream &operator>>(QDataStream &stream, Message &msg);

QDebug operator<<(QDebug stream, const Message &msg);




#endif // MESSAGE_H
