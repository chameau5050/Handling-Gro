#include <QJsonArray>
#include <QJsonObject>
#include "Commandwindow.h"
#include "ui_Commandwindow.h"
#include "Comm/Dataframe.h"

CommandWindow::CommandWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CommandWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->set_J1,SIGNAL(valueChanged(int)),this,SLOT(sendJointPosition(int)));
    QObject::connect(ui->set_J2,SIGNAL(valueChanged(int)),this,SLOT(sendJointPosition(int)));
    QObject::connect(ui->set_J3,SIGNAL(valueChanged(int)),this,SLOT(sendJointPosition(int)));
    QObject::connect(ui->set_J4,SIGNAL(valueChanged(int)),this,SLOT(sendJointPosition(int)));
    QObject::connect(ui->ConnectCommand, SIGNAL(pressed ()),this, SLOT(connectSocket()));

    socket = new QTcpSocket();

}

CommandWindow::~CommandWindow()
{
    delete ui;
    delete socket;
}


void CommandWindow::connectSocket()
{
     socket->connectToHost("127.0.0.1",50000);
}

void CommandWindow::readData()
{
    qint64 bytes = socket->bytesAvailable();
    if(bytes >0)
    {
        char* buffer = new char[bytes];
        int nbrRead =  socket->read(buffer,bytes);
        //insert acc here
        delete[] buffer;
    }
}


void CommandWindow::sendJointPosition(int val)
{
    int message[4];
    message[0] = ui->set_J1->value();
    message[1] = ui->set_J2->value();
    message[2] = ui->set_J3->value();
    message[3] = ui->set_J4->value();

    ControlMessage msg(1,4,message);
    sendControlMessage(&msg);
}

void CommandWindow::sendControlMessage(ControlMessage* msg)
{
    QJsonObject recordObject;
    recordObject.insert("type",QJsonValue::fromVariant(msg->getType()));
    recordObject.insert("PLS",QJsonValue::fromVariant(msg->getPayLoadSize()));

    if(msg->getPayLoadSize() > 0){

        QJsonArray array;
        for(int x = 0; x < msg->getPayLoadSize();x++)
        {
            array.append(QJsonValue::fromVariant(msg->getPayload()[x]));
        }

        recordObject.insert("data",array);
    }
    sendJSon(QJsonDocument(recordObject));
}


void CommandWindow::sendJSon(QJsonDocument doc)
{
    QJsonDocument allo;
    QByteArray json = doc.toJson(QJsonDocument::JsonFormat::Compact);
    DataFrame frame(1,json.data(),json.count());

     qint64 x = socket->write(frame.toRawData(),frame.getLength());
}


/*
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_server = new QTcpServer(this);
    Sendsock = new QTcpSocket(this);

    QObject::connect(ui->StartServerButton, SIGNAL(pressed ()),this, SLOT(startServer()));
    QObject::connect(ui->showRemotInfo, SIGNAL(pressed ()),this, SLOT(showRemoteInfo()));
    QObject::connect(ui->connectSocket, SIGNAL(pressed ()),this, SLOT(connectSocket()));
    QObject::connect(ui->sendMessage, SIGNAL(pressed ()),this, SLOT(sendMessage()));
}

void MainWindow::startServer()
{
    m_server->setMaxPendingConnections(2);
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
    //list.at(0).toIPv4Address()
    QHostAddress add = QHostAddress("192.168.50.51");
    QHostAddress::LocalHost;

    m_server->listen(QHostAddress("192.168.0.112"),6565);
    ui->messageLabel->setText(QHostInfo(1).hostName());
    QObject::connect(m_server, SIGNAL(newConnection()),this, SLOT(SocketConnected()));
}

void MainWindow::SocketConnected()
{
    sock = m_server->nextPendingConnection();
    QObject::connect(sock, SIGNAL(disconnected()),this, SLOT(SocketDisConnected()));
    QObject::connect(sock, SIGNAL(readyRead()),this, SLOT(checkForData()));
}

void MainWindow::SocketDisConnected()
{
    delete sock;
}

void MainWindow::checkForData()
{
    qint64 bytes = sock->bytesAvailable();
    if(bytes >0)
    {
        QString a =(sock->readAll());
        ui->messageLabel->setText(a);
    }
}

void MainWindow::showRemoteInfo()
{
    QString info ="";
    info += "address: " + sock->peerAddress().toString();
    info += "\nport: "    + QString::number(int(sock->peerPort()));
    info += "\nname:" + sock->peerName();
    ui->textWindow->setPlainText(info);
}

void MainWindow::connectSocket()
{
    QHostInfo().hostName();
    Sendsock->connectToHost(ui->Ip->text(),6565);

}

void MainWindow::sendMessage()
{
    Sendsock->write("patate",7);
}
*/

