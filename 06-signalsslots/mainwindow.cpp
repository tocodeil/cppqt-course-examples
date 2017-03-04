#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*
    QObject::connect(ui->from, &QLineEdit::textChanged,
                     this, &MainWindow::copyTextFromEditToLabel);
                     */
    /*
    QObject::connect(ui->from, &QLineEdit::textChanged,
                     this, &MainWindow::copyTextFromSignal);
                     */

    QObject::connect(ui->from, &QLineEdit::textChanged,
                     ui->to, &QLabel::setText);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::copyTextFromEditToLabel()
{
    ui->to->setText(ui->from->text());
}

void MainWindow::copyTextFromSignal(QString newText)
{
    ui->to->setText(newText);
}
