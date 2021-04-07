#include <QJsonArray>
#include <QJsonObject>
#include "Commandwindow.h"
#include "ui_Commandwindow.h"
#include "Comm/Dataframe.h"
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QStringBuilder>

CommandWindow::CommandWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CommandWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->sendCommend,SIGNAL(pressed()),this, SLOT(sendJointParameters()));
    QObject::connect(ui->ConnectCommand, SIGNAL(pressed()),this, SLOT(connectSocket()));
    QObject::connect(ui->setHome, SIGNAL(pressed()),this, SLOT(setHome()));
    QObject::connect(ui->goToHome, SIGNAL(pressed()),this, SLOT(goHome()));
    QObject::connect(ui->zeroButton, SIGNAL(pressed()),this, SLOT(zeroIn()));
    QObject::connect(ui->loadFileB, SIGNAL(pressed()),this, SLOT(loadFile()));
    QObject::connect(ui->saveFileB, SIGNAL(pressed()),this, SLOT(saveFile()));
    QObject::connect(ui->runFileB, SIGNAL(pressed()),this, SLOT(runFile()));
    QObject::connect(ui->loadFileName, SIGNAL(pressed()),this, SLOT(openFile()));
    QObject::connect(ui->saveFileName, SIGNAL(pressed()),this, SLOT(saveFileAs()));
    QObject::connect(ui->cmd_moveHere, SIGNAL(pressed()),this, SLOT(commandMoveHere()));
    QObject::connect(ui->cmd_goHome, SIGNAL(pressed()),this, SLOT(commandGoHome()));
    QObject::connect(ui->cmd_setHomeHere, SIGNAL(pressed()),this, SLOT(commandSetHomeHere()));
    QObject::connect(ui->cmd_openGripper, SIGNAL(pressed()),this, SLOT(commandOpenGripper()));
    QObject::connect(ui->cmd_closeGripper, SIGNAL(pressed()),this, SLOT(commandCloseGripper()));
    QObject::connect(ui->jointMode, SIGNAL(pressed()),this, SLOT(hideCartesian()));
    QObject::connect(ui->cartMode, SIGNAL(pressed()),this, SLOT(hideJoint()));
    QObject::connect(ui->openGripperB, SIGNAL(pressed()),this, SLOT(openGripper()));
    QObject::connect(ui->closeGripperB, SIGNAL(pressed()),this, SLOT(closeGripper()));

    ui->set_C1->hide();
    ui->set_C2->hide();
    ui->set_C3->hide();
    ui->paramLabel1->setText("Joint 1");
    ui->paramLabel2->setText("Joint 2");
    ui->paramLabel3->setText("Joint 3");
    ui->paramLabel4->setText("Joint 4");


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

void CommandWindow::openGripper()
{
    ControlMessage msg(CONTROL_MESSAGE_ID::OPEN_GRIPPER);
    sendControlMessage(&msg);
}

void CommandWindow::closeGripper()
{
    ControlMessage msg(CONTROL_MESSAGE_ID::CLOSE_GRIPPER);
    sendControlMessage(&msg);
}

void CommandWindow::hideJoint()
{
    ui->set_J4->hide();
    ui->set_C1->hide();
    ui->set_C2->hide();
    ui->set_C3->hide();
    ui->paramLabel1->setText("X");
    ui->paramLabel2->setText("Y");
    ui->paramLabel3->setText("Z");
    ui->paramLabel4->setText(" ");
}
void CommandWindow::hideCartesian()
{
    ui->set_C1->hide();
    ui->set_C2->hide();
    ui->set_C3->hide();
    ui->set_J4->show();
    ui->paramLabel1->setText("Joint 1");
    ui->paramLabel2->setText("Joint 2");
    ui->paramLabel3->setText("Joint 3");
    ui->paramLabel4->setText("Joint 4");
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
        message[0] = ui->set_J1->value();
        message[1] = ui->set_J2->value();
        message[2] = ui->set_J3->value();
        ControlMessage msg(CONTROL_MESSAGE_ID::SET_CARTESIEN_POSITION,3,message);
        sendControlMessage(&msg);
    }
}

void CommandWindow::setHome()
{
    if (ui->jointMode->isChecked())
    {
        home_joint[0] = ui->set_J1->value();
        home_joint[1] = ui->set_J2->value();
        home_joint[2] = ui->set_J3->value();
        home_joint[3] = ui->set_J4->value();
        ControlMessage msg(CONTROL_MESSAGE_ID::SET_HOME,4,home_joint);
        sendControlMessage(&msg);
    }
    else if (ui->cartMode->isChecked())
    {
        home_cart[0] = ui->set_J1->value();
        home_cart[1] = ui->set_J2->value();
        home_cart[2] = ui->set_J3->value();
        ControlMessage msg(CONTROL_MESSAGE_ID::SET_HOME,3,home_cart);
        sendControlMessage(&msg);
    }
}

void CommandWindow::goHome()
{
    ControlMessage msg(CONTROL_MESSAGE_ID::GOTO_HOME);
    sendControlMessage(&msg);
}

void CommandWindow::zeroIn()
{
    int message[5] = {1, 1, 1, 1, 1};
    ControlMessage msg(CONTROL_MESSAGE_ID::RESET_ENCODER,5,message);
    sendControlMessage(&msg);
}

void CommandWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Text files (*.txt)"));
    ui->progFileName->setText(fileName);
}

void CommandWindow::saveFileAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "/home/untitled.txt", tr("Text files (*.txt)"));
    ui->progFileName->setText(fileName);
}

void CommandWindow::commandMoveHere()
{
    int message[4];
    message[0] = ui->set_J1->value();
    message[1] = ui->set_J2->value();
    message[2] = ui->set_J3->value();
    message[3] = ui->set_J4->value();
    QString line = "Joint,"
            % QString::number(message[0])
            % ','
            % QString::number(message[1])
            % ','
            % QString::number(message[2])
            % ','
            % QString::number(message[3]);
    ui->dispFile->appendPlainText(line);
}
void CommandWindow::commandGoHome()
{
    QString line = "GoHome";
    ui->dispFile->appendPlainText(line);
}
void CommandWindow::commandSetHomeHere()
{
    int message[4];
    message[0] = ui->set_J1->value();
    message[1] = ui->set_J2->value();
    message[2] = ui->set_J3->value();
    message[3] = ui->set_J4->value();
    QString line = "HomeJoint,"
            % QString::number(message[0])
            % ','
            % QString::number(message[1])
            % ','
            % QString::number(message[2])
            % ','
            % QString::number(message[3]);
    ui->dispFile->appendPlainText(line);
}
void CommandWindow::commandOpenGripper()
{
    QString line = "GripperOpen";
    ui->dispFile->appendPlainText(line);
}
void CommandWindow::commandCloseGripper()
{
    QString line = "GripperClose";
    ui->dispFile->appendPlainText(line);
}

void CommandWindow::loadFile()
{
    QFile f(ui->progFileName->text());
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
    QFile f(ui->progFileName->text());
    if (f.open(QFile::WriteOnly))
    {
        QTextStream stream(&f);
        QString content = ui->dispFile->toPlainText();
        stream << content;
        f.close();
    }
}

bool CommandWindow::sendCartesianPosition(QStringList command)
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

bool CommandWindow::sendJointPosition(QStringList command)
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
    QFile f(ui->progFileName->text());
    if (f.open(QFile::ReadOnly))
    {
        QTextStream stream(&f);
        QString line;
        bool ok;
        do
        {
            line = stream.readLine();
            QStringList command = line.split(QString(','));
            if (command[0] == QString("Joint"))
            {
               ok = sendJointPosition(command);
            }
            else if (command[0] == QString("Cartesian"))
            {
               ok = sendCartesianPosition(command);
            }
            else if (command[0] == QString("HomeJoint"))
            {
                home_joint[0] = command[1].toInt(&ok,10);
                home_joint[1] = command[2].toInt(&ok,10);
                home_joint[2] = command[3].toInt(&ok,10);
                home_joint[3] = command[4].toInt(&ok,10);
                ControlMessage msg(CONTROL_MESSAGE_ID::SET_HOME,4,home_joint);
                sendControlMessage(&msg);
            }
            else if (command[0] == QString("HomeCartesian"))
            {
                home_cart[0] = command[1].toInt(&ok,10);
                home_cart[1] = command[2].toInt(&ok,10);
                home_cart[2] = command[3].toInt(&ok,10);
                ControlMessage msg(CONTROL_MESSAGE_ID::SET_HOME,3,home_cart);
                sendControlMessage(&msg);
            }
            else if (command[0] == QString("GoHome"))
            {
                ControlMessage msg(CONTROL_MESSAGE_ID::GOTO_HOME);
                sendControlMessage(&msg);
            }
            else if (command[0] == QString("GripperOpen"))
            {
                ControlMessage msg(CONTROL_MESSAGE_ID::OPEN_GRIPPER);
                sendControlMessage(&msg);
            }
            else if (command[0] == QString("GripperClose"))
            {
                ControlMessage msg(CONTROL_MESSAGE_ID::CLOSE_GRIPPER);
                sendControlMessage(&msg);
            }
            else
            {
                QMessageBox::warning(this, tr("Command error"), "WARNING: " + line + " is not a valid command. This command will be skipped",QMessageBox::Close);
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

