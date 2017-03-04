#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include "imageconverter.h"

MainWindow::MainWindow(ImageConverter &converter, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_converter(converter)
{
    ui->setupUi(this);
    QObject::connect(ui->btnSelectFiles, &QPushButton::clicked,
                     this, &MainWindow::selectFiles);
    QObject::connect(ui->btnConvert, &QPushButton::clicked,
                     this, &MainWindow::convert);

    QObject::connect(&m_converter, &ImageConverter::convertDone,
                     this, &MainWindow::handleConvertDone);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::selectFiles()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(
                this,
                "Select File Names",
                QString(),
                "Images (*.png *.jpg)");

    ui->listWidget->clear();
    ui->listWidget->addItems(fileNames);
}

void MainWindow::convert()
{
    QStringList fileNames;

    QList<QListWidgetItem *> items = ui->listWidget->findItems("", Qt::MatchContains);
    for (auto i : items)
    {
        fileNames.push_back(i->text());
    }
    ui->progressBar->setMaximum(fileNames.size());
    QMetaObject::invokeMethod(
                &m_converter,
                "convert",
                Q_ARG(QStringList, fileNames));
}

void MainWindow::handleConvertDone(QString fileName)
{
    auto items = ui->listWidget->findItems(fileName, Qt::MatchExactly);
    ui->progressBar->setValue(ui->progressBar->value() + 1);
    for (auto item : items)
    {
        item->setText("done! ... " + item->text());
    }
}
