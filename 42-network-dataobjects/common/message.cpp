#include "message.h"

QDataStream &operator<<(QDataStream &stream, const Message &msg)
{
    stream << static_cast<int>(msg.type);
    stream << msg.data;
    return stream;
}

QDataStream &operator>>(QDataStream &stream, Message &msg)
{
    int msgType;
    stream >> msgType;
    stream >> msg.data;

    msg.type = static_cast<MessageType>(msgType);
    return stream;
}

QDebug operator<<(QDebug stream, const Message &msg)
{
    stream << "[Message]";
    stream << msg.type;
    stream << msg.data;
}
