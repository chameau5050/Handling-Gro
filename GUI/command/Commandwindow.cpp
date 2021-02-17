#include "Commandwindow.h"
#include "ui_Commandwindow.h"

CommandWindow::CommandWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CommandWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->set_J1,SIGNAL(valueChanged(int)),this,SLOT(envoieValeur(int)));
    QObject::connect(ui->set_J2,SIGNAL(valueChanged(int)),this,SLOT(envoieValeur(int)));
    QObject::connect(ui->set_J3,SIGNAL(valueChanged(int)),this,SLOT(envoieValeur(int)));
    QObject::connect(ui->set_J4,SIGNAL(valueChanged(int)),this,SLOT(envoieValeur(int)));
}

CommandWindow::~CommandWindow()
{
    delete ui;
}

void CommandWindow::envoieValeur(int val)
{
    int message[4];
    message[0] = ui->set_J1->value();
    message[1] = ui->set_J2->value();
    message[2] = ui->set_J3->value();
    message[3] = ui->set_J4->value();
}
