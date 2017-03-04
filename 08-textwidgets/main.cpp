#include "mainwindow.h"
#include <QApplication>
#include "echobox.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EchoBox w;
    w.show();

    return a.exec();
}
