#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setAlignment(Qt::AlignJustify | Qt::AlignVCenter);
    QRegExpValidator *v = new QRegExpValidator(QRegExp("^\\d{2}-?\\d{7}$"), this);
    ui->phone->setValidator(v);

    QObject::connect(ui->textEdit, &QTextEdit::textChanged,
                     this, &MainWindow::showCharacterCount);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showCharacterCount()
{
    int count = ui->textEdit->toPlainText().size();
    ui->counter->setText(QString("Characters: %1").arg(count));
}
