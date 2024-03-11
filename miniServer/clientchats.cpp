#include "clientchats.h"
#include "ui_clientchats.h"


ClientChats::ClientChats(QTcpSocket *client, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ClientChats)
{
    ui->setupUi(this);
    _client = new ClientManager(client,this);

    connect(_client, &ClientManager::disconnected, this, &ClientChats::clientDisconnected);
    connect(_client, &ClientManager::textMessageReceived, this, &ClientChats::textMessageReceived);
    connect(_client, &ClientManager::nameChanged, this, &ClientChats::onClientNameChanged);
    connect(ui->leMessage, &QLineEdit::textChanged, _client, &ClientManager::sendIsTyping);
    connect(_client, &ClientManager::isTyping, this, &ClientChats::onTyping);
    connect(_client, &ClientManager::statusChanged, this, &ClientChats::statusChanged);

}

ClientChats::~ClientChats()
{
    delete ui;
}


void ClientChats::disconnect()
{
    _client->disconnectFromHost();
}


void ClientChats::clientDisconnected()
{
    ui->btnSend->setEnabled(false);

}

void ClientChats::on_btnSend_clicked()
{
    auto message = ui->leMessage->text().trimmed();
    _client->sendMessage(message);
    ui->leMessage->setText("");
    ui->listMessages->addItem(message);
}


void ClientChats::textMessageReceived(QString message, QString receiver)
{
    if (receiver == "Server" || receiver == "All") {
        ui->listMessages->addItem(message);
    }
    if(receiver != "Server"){
        emit textForOtherClients(message, receiver, _client->name());
    }
}
void ClientChats::onClientNameChanged(QString prevName, QString name)
{
    qInfo() << prevName << " to " << name;
    emit clientNameChanged(prevName, name);
}

void ClientChats::onTyping()
{
    emit isTyping(QString("%1 is typing...").arg(_client->name()));
}

