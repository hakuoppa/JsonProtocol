#ifndef CLIENTCHATS_H
#define CLIENTCHATS_H

#include "clientmanager.h"

#include <QTcpSocket>
#include <QWidget>

namespace Ui {
class ClientChats;
}

class ClientChats : public QWidget
{
    Q_OBJECT

public:
    explicit ClientChats(QTcpSocket *client, QWidget *parent = nullptr);
    ~ClientChats();

        void disconnect();
signals:
    void textForOtherClients(QString message, QString receiver, QString sender);
    void clientNameChanged(QString prevName, QString name);
    void statusChanged(ChatProtocol::Status status);
    void isTyping(QString message);



private slots:

    void clientDisconnected();
    void on_btnSend_clicked();

    void textMessageReceived(QString message, QString receiver);

    void onClientNameChanged(QString prevName, QString name);

    void onTyping();


private:
    Ui::ClientChats *ui;
    ClientManager *_client;
};

#endif // CLIENTCHATS_H
