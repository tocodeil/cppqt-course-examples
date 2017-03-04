#include "mainwindow.h"
#include <QApplication>
#include "mypainter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    MyPainter p;
//    p.show();

    return a.exec();
}
