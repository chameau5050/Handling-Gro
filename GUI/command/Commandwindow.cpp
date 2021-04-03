#include <QJsonArray>
#include <QJsonObject>
#include "Commandwindow.h"
#include "ui_Commandwindow.h"
#include "Comm/Dataframe.h"
#include <QDir>

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
    QObject::connect(ui->loadFileB, SIGNAL(pressed()),this, SLOT(loadFile()));
    QObject::connect(ui->saveFileB, SIGNAL(pressed()),this, SLOT(saveFile()));
    QObject::connect(ui->runFileB, SIGNAL(pressed()),this, SLOT(runFile()));

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

        ControlMessage msg(CONTROL_MESSAGE_ID::SET_JOIN_POSITION,4,message);
        sendControlMessage(&msg);
    }
    else if (ui->cartMode->isChecked()) {
        int message[3];
        message[0] = ui->set_C1->value();
        message[1] = ui->set_C2->value();
        message[2] = ui->set_C3->value();
        ControlMessage msg(CONTROL_MESSAGE_ID::SET_CARTESIEN_POSITION,3,message);
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

void CommandWindow::loadFile()
{
    QDir dir(ui->progFileDir->text());
    QString nameFile = ui->progFileName->text();
    QString findFile = dir.filePath(nameFile);
    QFile f(findFile);
    if (f.open(QFile::ReadOnly))
    {
        ui->dispFile->clear();
        QTextStream stream(&f);
        QString line;
        do
        {
            line = stream.readLine();
            ui->dispFile->appendPlainText(line);
        } while(!stream.atEnd());
        f.close();
    }
}

void CommandWindow::saveFile()
{
    QDir dir(ui->progFileDir->text());
    QString nameFile = ui->progFileName->text();
    QString findFile = dir.filePath(nameFile);
    QFile f(findFile);
    if (f.open(QFile::WriteOnly))
    {
        QTextStream stream(&f);
        QString content = ui->dispFile->toPlainText();
        stream << content;
        f.close();
    }
}

bool CommandWindow::sendCartesienPosition(QStringList command)
{
    bool ok;
    int message[3];
    message[0] = command[1].toInt(&ok,10);
    message[1] = command[2].toInt(&ok,10);
    message[2] = command[3].toInt(&ok,10);

    ControlMessage msg(CONTROL_MESSAGE_ID::SET_CARTESIEN_POSITION,3,message);
    sendControlMessage(&msg);
    return ok;
}

bool CommandWindow::sendJoinPosition(QStringList command)
{
    bool ok;
    int message[4];
    message[0] = command[1].toInt(&ok,10);
    message[1] = command[2].toInt(&ok,10);
    message[2] = command[3].toInt(&ok,10);
    message[3] = command[4].toInt(&ok,10);

    ControlMessage msg(CONTROL_MESSAGE_ID::SET_JOIN_POSITION,4,message);
    sendControlMessage(&msg);
    return ok;
}

void CommandWindow::runFile()
{
    QDir dir(ui->progFileDir->text());
    QString nameFile = ui->progFileName->text();
    QString findFile = dir.filePath(nameFile);
    QFile f(findFile);
    if (f.open(QFile::ReadOnly))
    {
        QTextStream stream(&f);
        QString line;
        bool ok;
        bool jointH = false;
        bool cartH = false;
        do
        {
            line = stream.readLine();
            QStringList command = line.split(QString(','));
            if (command[0] == QString('J'))
            {
               ok = sendJoinPosition(command);
            }
            else if (command[0] == QString('C'))
            {
               ok = sendCartesienPosition(command);
            }
            else if (command[0] == QString("HJ"))
            {
                home_joint[0] = command[1].toInt(&ok,10);
                home_joint[1] = command[2].toInt(&ok,10);
                home_joint[2] = command[3].toInt(&ok,10);
                home_joint[3] = command[4].toInt(&ok,10);
                jointH = true;
                cartH = false;
            }
            else if (command[0] == QString("HC"))
            {
                home_cart[0] = command[1].toInt(&ok,10);
                home_cart[1] = command[2].toInt(&ok,10);
                home_cart[2] = command[3].toInt(&ok,10);
                cartH = true;
                jointH = false;
            }
            else if (command[0] == QString("GH"))
            {
                if (cartH)
                {
                    //ControlMessage msg(7,3,home_cart);
                    //sendControlMessage(&msg);
                }
                else if (jointH)
                {
                    //ControlMessage msg(7,3,home_joint);
                    //sendControlMessage(&msg);
                }
            }
            else if (command[0] == QString("GO"))
            {
                //Open gripper command
            }
            else if (command[0] == QString("GC"))
            {
                //Close gripper command
            }
        } while(!stream.atEnd());
        f.close();
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
    QByteArray json = doc.toJson(QJsonDocument::JsonFormat::Compact);
    DataFrame frame(1,json.data(),json.count());

     qint64 x = socket->write(frame.toRawData(),frame.getLength());
}

