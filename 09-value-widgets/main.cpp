#include "mainwindow.h"
#include "buttons.h"
#include "values.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Buttons b;
    b.show();

    Values v;
    v.show();

    return a.exec();
}
