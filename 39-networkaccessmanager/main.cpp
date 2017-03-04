#include "mainwindow.h"
#include <QApplication>
#include <QtNetwork>
#include <QDebug>
#include <iostream>

void showSupportedSchemes()
{
    QNetworkAccessManager nam;
    qDebug() << nam.supportedSchemes();
}

int showWeather(int argc, char **argv)
{
    QApplication a(argc, argv);
    QNetworkAccessManager nam;
    QNetworkRequest req(QUrl("http://wttr.in/israel"));
    req.setRawHeader("User-Agent", "curl/7.51.0");

    nam.get(req);
    QObject::connect(&nam, &QNetworkAccessManager::finished,
                     [&a](QNetworkReply *reply) {
        std::cout << reply->readAll().toStdString();
        reply->deleteLater();
        a.quit();
    });
    return a.exec();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    showSupportedSchemes();
//    return showWeather(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
