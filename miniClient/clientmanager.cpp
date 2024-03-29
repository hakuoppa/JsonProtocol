#include "clientmanager.h"


ClientManager::ClientManager(QHostAddress ip, ushort port, QObject *parent)
    : QObject{parent},
    _ip(ip),
    _port(port)
{
    setupClient();
}

void ClientManager::connectToServer()
{
    _socket->connectToHost(_ip, _port);
    qInfo() <<  "connectToHost" ;
}

void ClientManager::disconnectToServer()
{
    _socket->disconnect();
}

void ClientManager::sendMessage(QString message, QString receiver)
{
    _socket->write(_protocol.textMessage(message, receiver));
}

void ClientManager::sendName(QString name)
{
    _socket->write(_protocol.setNameMessage(name));
    qInfo() << "Send name " << name ;
}


void ClientManager::sendIsTyping()
{
    _socket->write(_protocol.isTypingMessage());

}

void ClientManager::sendStatus(ChatProtocol::Status status)
{
    _socket->write(_protocol.setStatusMessage(status));
    qInfo() << "Send Status " << status;
}




void ClientManager::readyRead()
{
    auto data = _socket->readAll();
    _protocol.loadData(data);
    qInfo() << "Protocol type: " << _protocol.type();
    switch (_protocol.type()) {
    case ChatProtocol::Text:
        emit textMessageReceived(_protocol.message());
        break;
    case ChatProtocol::SetName:
        emit nameChanged(_protocol.name());
        break;
    case ChatProtocol::IsTyping:
        emit isTyping();
        break;
    case ChatProtocol::SetStatus:
        emit statusChanged(_protocol.status());
        break;
    case ChatProtocol::ConnectionACK:
        emit connectionACK(_protocol.myName(), _protocol.clientsName());
        break;
    case ChatProtocol::NewClient:
        emit newClientConnectedToServer(_protocol.clientName());
        break;
    case ChatProtocol::ClientDisconnected:
        emit clientDisconnected(_protocol.clientName());
        break;
    case ChatProtocol::ClientName:
        emit clientNameChanged(_protocol.prevName(), _protocol.clientName());
        break;
    default:
        break;
    }
}

void ClientManager::setupClient()
{
    _socket = new QTcpSocket(this);
    connect(_socket, &QTcpSocket::connected, this, &ClientManager::connected);
    connect(_socket, &QTcpSocket::disconnected, this, &ClientManager::disconnected);
    connect(_socket, &QTcpSocket::readyRead, this, &ClientManager::readyRead);
}

/*
 * void ClientManager::sendFile()
{
    _socket->write(_protocol.setFileMessage(_tmpFileName));
}
*/


