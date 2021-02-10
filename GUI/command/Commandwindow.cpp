#include "Commandwindow.h"
#include "ui_Commandwindow.h"

CommandWindow::CommandWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CommandWindow)
{
    ui->setupUi(this);
}

CommandWindow::~CommandWindow()
{
    delete ui;
}
