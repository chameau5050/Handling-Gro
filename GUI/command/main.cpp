#include "Commandwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CommandWindow w;
    w.show();
    return a.exec();
}
