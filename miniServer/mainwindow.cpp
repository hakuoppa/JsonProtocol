#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupServer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newClientConnected(QTcpSocket *client)
{
    auto id = client->property("id").toInt();
    ui->listClients->addItem(QString("New Client added: %1").arg(id));
    auto chatWidget= new ClientChats(client, ui->tabChats);
    ui->tabChats->addTab(chatWidget, QString("Client (%1)").arg(id));

    connect(chatWidget, &ClientChats::clientNameChanged, this, &MainWindow::setClientName);
    connect(chatWidget, &ClientChats::statusChanged, this, &MainWindow::setClientStatus);
    connect(chatWidget, &ClientChats::isTyping, [this](QString name){
        this->statusBar()->showMessage(name, 750);
    });

    connect(chatWidget, &ClientChats::textForOtherClients, _server, &ServerManager::onTextForOtherClients);



}

void MainWindow::clientDisconnected(QTcpSocket *client)
{
    auto id = client->property("id").toInt();
    ui->listClients->addItem(QString("Client disconnected: %1").arg(id));
    on_tbClientsChat_tabCloseRequested(id);
}


void MainWindow::setupServer()
{
    _server = new ServerManager();
    connect(_server, &ServerManager::newClientConnected, this, &MainWindow::newClientConnected);
    connect(_server, &ServerManager::clientDisconnected, this, &MainWindow::clientDisconnected);

}

void MainWindow::setClientName(QString prevName, QString name)
{
    qInfo() << prevName << " to " << name ;
    auto widget = qobject_cast<QWidget *>(sender());
    auto index = ui->tabChats->indexOf(widget);
    ui->tabChats->setTabText(index, name);

    _server->notifyOtherClients(prevName, name);
}
void MainWindow::on_tbClientsChat_tabCloseRequested(int index)
{
    auto chatWidget = qobject_cast<ClientChats *>(ui->tabChats->widget(index));
    chatWidget->disconnect();
    ui->tabChats->removeTab(index);
}
void MainWindow::setClientStatus(ChatProtocol::Status status)
{
    auto widget = qobject_cast<QWidget *>(sender());
    auto index = ui->tabChats->indexOf(widget);
    QString iconName = ":/icons/";
    switch (status) {
    case ChatProtocol::Available:
        iconName.append("available.png");
        break;
    case ChatProtocol::Away:
        iconName.append("away.png");
        break;
    case ChatProtocol::Busy:
        iconName.append("busy.png");
        break;
    default:
        iconName = "";
        break;

    }

    auto icon = QIcon(iconName);
    ui->tabChats->setTabIcon(index, icon);
}
