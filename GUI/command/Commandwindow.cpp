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
    QObject::connect(ui->sendCommend,SIGNAL(pressed()),this, SLOT(sendJointParameters()));
    QObject::connect(ui->ConnectCommand, SIGNAL(pressed()),this, SLOT(connectSocket()));
    QObject::connect(ui->setHome, SIGNAL(pressed()),this, SLOT(saveHome()));
    QObject::connect(ui->goToHome, SIGNAL(pressed()),this, SLOT(goHome()));


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
    if (ui->jointMode->isChecked())
    {
        int message[4];
        message[0] = ui->set_J1->value();
        message[1] = ui->set_J2->value();
        message[2] = ui->set_J3->value();
        message[3] = ui->set_J4->value();

        ControlMessage msg(7,8,message);
        sendControlMessage(&msg);
    }
    else if (ui->cartMode->isChecked()) {
        int message[3];
        message[0] = ui->set_C1->value();
        message[1] = ui->set_C2->value();
        message[2] = ui->set_C3->value();
        ControlMessage msg(7,3,message);
        sendControlMessage(&msg);
    }
}

void CommandWindow::saveHome()
{
    if (ui->jointMode->isChecked())
    {
        home_joint[0] = ui->set_J1->value();
        home_joint[1] = ui->set_J2->value();
        home_joint[2] = ui->set_J3->value();
        home_joint[3] = ui->set_J4->value();
    }
    else if (ui->cartMode->isChecked())
    {
        home_cart[0] = ui->set_C1->value();
        home_cart[1] = ui->set_C2->value();
        home_cart[2] = ui->set_C3->value();
    }
}

void CommandWindow::goHome()
{
    if (ui->jointMode->isChecked())
    {
        ui->set_J1->setValue(home_joint[0]);
        ui->set_J2->setValue(home_joint[1]);
        ui->set_J3->setValue(home_joint[2]);
        ui->set_J4->setValue(home_joint[3]);
    }
    else if (ui->cartMode->isChecked())
    {
        ui->set_C1->setValue(home_cart[0]);
        ui->set_C2->setValue(home_cart[1]);
        ui->set_C3->setValue(home_cart[2]);
    }
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

