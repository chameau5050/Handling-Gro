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
private slots:

private:
    Ui::CommandWindow *ui;
    /*QLCDNumber *m_showJ1;
    QLCDNumber *m_showJ2;
    QLCDNumber *m_showJ3;
    QLCDNumber *m_showJ4;
    QSlider *m_setJ1;
    QSlider *m_setJ2;
    QSlider *m_setJ3;
    QSlider *m_setJ4;
    QLabel *m_nameJ1;
    QLabel *m_nameJ2;
    QLabel *m_nameJ3;
    QLabel *m_nameJ4;*/

};
#endif // COMMANDWINDOW_H
