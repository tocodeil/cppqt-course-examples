#include "mainwindow.h"
#include <QApplication>
#include <QProcess>

int waitForProcessDemo()
{
    QStringList args = { "https://www.tocode.co.il" };
    return QProcess::execute("/Applications/Google Chrome.app/Contents/MacOS/Google Chrome", args);
}

int cpEtcShellsToCwd(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QStringList args = { "/etc/shells", "." };
    QProcess proc;
    proc.start("cp", args);
    // Option1: cast function pointers
    QObject::connect(&proc, static_cast<void (QProcess::*)(int)>(&QProcess::finished),
                     &a, &QCoreApplication::quit);

    // Option2: use old SIGNAL/SLOT syntax
//    QObject::connect(&proc, SIGNAL(finished(int)),
//                     &a, SLOT(quit()));
    return a.exec();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
