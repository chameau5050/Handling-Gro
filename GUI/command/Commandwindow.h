#ifndef COMMANDWINDOW_H
#define COMMANDWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QLCDNumber>
#include <QSlider>
#include <QTcpSocket>
#include <QJsonDocument>

#include "Comm/Controlmessage.h"
#include "Comm/Accumulator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CommandWindow; }
QT_END_NAMESPACE

class CommandWindow : public QMainWindow, MessageInterpretor
{
    Q_OBJECT
public:
    CommandWindow(QWidget *parent = nullptr);
    ~CommandWindow();
    void sendJSon(QJsonDocument doc);
    void sendControlMessage(ControlMessage* msg);
    bool messageReceved(char* rawDataFrame,unsigned int lenght);
public slots:
    void sendJointPosition(int val);
    void connectSocket();
    void readData();
private:
    Ui::CommandWindow *ui;
    QTcpSocket* socket;
    Accumulator* acc;
};
#endif // COMMANDWINDOW_H
