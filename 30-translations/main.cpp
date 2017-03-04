#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLocale>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLocale::setDefault(QLocale::Hebrew);
    QTranslator tr;
    tr.load(":app.qm");
    a.installTranslator(&tr);
    MainWindow w;
    w.setLayoutDirection(Qt::RightToLeft);
    w.show();

    return a.exec();
}
