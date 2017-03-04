#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("tocode");
    QCoreApplication::setApplicationName("28-settings");

    MainWindow w;
    w.show();

    return a.exec();
}
