#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QNetworkReply>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(&m_nam, &QNetworkAccessManager::finished,
                     this, &MainWindow::handleSearchResults);
    QObject::connect(ui->btnSearch, &QPushButton::clicked,
                     this, &MainWindow::startSearch);
    QObject::connect(ui->eSearch, &QLineEdit::returnPressed,
                     this, &MainWindow::startSearch);
    ui->progressBar->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startSearch()
{
    QString q = ui->eSearch->text();
    if (q.isEmpty()) return;

    QNetworkRequest req(QUrl(QString("http://omdbapi.com?s=%1").arg(q)));
    QNetworkReply *reply = m_nam.get(req);
    QObject::connect(reply, &QNetworkReply::downloadProgress,
                     this, &MainWindow::showProgress);

    ui->listWidget->clear();
    ui->progressBar->show();
    ui->progressBar->setRange(0, 0);

    if (m_activeReply)
    {
        m_activeReply->abort();
        m_activeReply = NULL;
    }
    m_activeReply = reply;
}

void MainWindow::handleSearchResults(QNetworkReply *reply)
{
    reply->deleteLater();
    // stop here for aborted replies
    if (!reply->isOpen()) return;

    // handle successful result
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    auto results = doc.object().value("Search").toArray();

    for (auto item: results)
    {
        auto movieData = item.toObject();
        ui->listWidget->addItem(movieData.value("Title").toString());
    }
    ui->progressBar->hide();
}

void MainWindow::showProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    if (bytesTotal > 0)
    {
        ui->progressBar->setValue(bytesReceived);
        ui->progressBar->setRange(0, bytesTotal);
    }
}
