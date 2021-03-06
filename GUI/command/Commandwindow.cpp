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
    /*QObject::connect(ui->set_J1,SIGNAL(valueChanged(int)),this,SLOT(sendJointPosition(int)));
    QObject::connect(ui->set_J2,SIGNAL(valueChanged(int)),this,SLOT(sendJointPosition(int)));
    QObject::connect(ui->set_J3,SIGNAL(valueChanged(int)),this,SLOT(sendJointPosition(int)));
    QObject::connect(ui->set_J4,SIGNAL(valueChanged(int)),this,SLOT(sendJointPosition(int)));*/
    QObject::connect(ui->sendCommend,SIGNAL(pressed ()),this, SLOT(sendJointParameters()));
    QObject::connect(ui->ConnectCommand, SIGNAL(pressed ()),this, SLOT(connectSocket()));

    socket = new QTcpSocket();
    acc = new Accumulator(this);

}

bool CommandWindow::messageReceved(char* rawDataFrame,unsigned int lenght)
{
    return true;
}

CommandWindow::~CommandWindow()
{
    delete ui;
    delete socket;
}


void CommandWindow::connectSocket()
{
    socket->connectToHost(ui->targetIp->text(),ui->targetPort->text().toInt());
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


void CommandWindow::sendJointParameters()
{
    int message[8];
    message[0] = ui->set_J1->value();
    message[1] = ui->set_J2->value();
    message[2] = ui->set_J3->value();
    message[3] = ui->set_J4->value();
    message[4] = ui->set_V1->value();
    message[5] = ui->set_V2->value();
    message[6] = ui->set_V3->value();
    message[7] = ui->set_V4->value();

    ControlMessage msg(7,8,message);
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

