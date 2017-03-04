#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include "imageconverter.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->btnSelectFiles, &QPushButton::clicked,
                     this, &MainWindow::selectFiles);
    QObject::connect(ui->btnConvert, &QPushButton::clicked,
                     this, &MainWindow::convert);

    m_converter = new ImageConverter(this);
    QObject::connect(m_converter, &ImageConverter::convertDone,
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
    m_converter->convert(fileNames);
}

void MainWindow::handleConvertDone(QString fileName)
{
    auto items = ui->listWidget->findItems(fileName, Qt::MatchExactly);
    for (auto item : items)
    {
        item->setText("done! ... " + item->text());
        // partial fix: process events after each finished item
//         qApp->processEvents();
    }
}
