#ifndef COMMANDWINDOW_H
#define COMMANDWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QLCDNumber>
#include <QSlider>

QT_BEGIN_NAMESPACE
namespace Ui { class CommandWindow; }
QT_END_NAMESPACE

class CommandWindow : public QMainWindow
{
    Q_OBJECT
public:
    CommandWindow(QWidget *parent = nullptr);
    ~CommandWindow();
public slots:
    void envoieValeur(int val);
private slots:

private:
    Ui::CommandWindow *ui;
};
#endif // COMMANDWINDOW_H
