#include "mainwindow.h"
#include <QApplication>
#include "imageconverter.h"
#include <QThread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImageConverter converter;
    QThread t;
    converter.moveToThread(&t);
    t.start();

    MainWindow w(converter);
    w.show();

    return a.exec();
}
