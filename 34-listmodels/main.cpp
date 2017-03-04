#include "mainwindow.h"
#include <QApplication>
#include "settingsmodel.h"
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("Model Demo");
    QCoreApplication::setOrganizationName("tocode");

    SettingsModel model;
    QListView lv;
    lv.setModel(&model);
    lv.show();

    return a.exec();
}
