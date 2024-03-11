#ifndef CHATPROTOCOL_H
#define CHATPROTOCOL_H

#include <QByteArray>
#include <QString>


class ChatProtocol
{
public:

    enum Status{
        None,
        Available,
        Away,
        Busy
    };

    enum MessageType{
        Text,
        IsTyping,
        SetName,
        SetStatus,
        InitSendingFile,
        AcceptSendingFile,
        RejectSendingFile,
        SendFile,
        ClientName,
        ConnectionACK,
        NewClient,
        ClientDisconnected
    };

    ChatProtocol();

    QByteArray isTypingMessage();
    QByteArray setNameMessage(QString name);
    QByteArray setStatusMessage(Status status);


    QByteArray setClientNameMessage(QString prevName, QString name);
    QByteArray textMessage(QString message, QString receiver);
    QByteArray setConnectionACKMessage(QString clientName, QStringList otherClients);
    QByteArray setNewClientMessage(QString clientName);
    QByteArray setClientDisconnectedMessage(QString clientName);

    void loadData(QByteArray data);

    const QString &clientName() const;
    const QString &prevName() const;
    const QString &message() const;
    const QString &name() const;

    MessageType type() const;    
    Status status() const;


    const QString &receiver() const
    {
        return _receiver;
    }

private:
    QByteArray getData(MessageType type, QString data);

    MessageType _type;
    QString _message;
    QString _name;;
    QString _receiver;
    Status _status;

};

#endif // CHATPROTOCOL_H
