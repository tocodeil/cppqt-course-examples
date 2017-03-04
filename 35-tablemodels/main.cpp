#include "mainwindow.h"
#include <QApplication>
#include "settingsmodel.h"
#include <QtWidgets>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("Model Demo");
    QCoreApplication::setOrganizationName("tocode");

    MainWindow w;
    w.show();

    return a.exec();
}
