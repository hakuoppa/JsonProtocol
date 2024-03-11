#ifndef CHATPROTOCOLJSON_H
#define CHATPROTOCOLJSON_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

class ChatProtocolJson
{
public:
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

    enum Status{
        None,
        Available,
        Away,
        Busy
    };

    ChatProtocol();

    QJsonObject textMessage(QString message, QString receiver);
    QJsonObject isTypingMessage();
    QJsonObject setNameMessage(QString name);
    QJsonObject setStatusMessage(Status status);
    QJsonObject setInitSendingFileMessage(QString fileName);

    QJsonObject setAcceptFileMessage();
    QJsonObject setRejectFileMessage();
    QJsonObject setFileMessage(QString fileName);

    void loadData(const QJsonObject &json);

    const QString &message() const;

    const QString &name() const;

    Status status() const;

    MessageType type() const;

    const QString &fileName() const;

    qint64 fileSize() const;

    const QByteArray &fileData() const;

    QString receiver() const;

    const QString &clientName() const;

    const QString &prevName() const;

    const QStringList &clientsName() const;

    const QString &myName() const;

private:
    QJsonObject getData(MessageType type, QString data);

    MessageType _type;
    QString _message;
    QString _name;
    Status _status;
    QString _fileName;
    qint64 _fileSize;
    QByteArray _fileData;
    QString _receiver;
    QString _clientName;

    QString _prevName;
    QStringList _clientsName;
    QString _myName;
};

#endif // CHATPROTOCOLJSON_H
