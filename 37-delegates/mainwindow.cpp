#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItemModel>
#include "shapedelegate.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStandardItemModel *model = new QStandardItemModel(this);
    QStringList shapes = { "triangle", "rectangle", "fivangle", "sixangle" };
    for (int i=0; i < shapes.size(); i++)
    {
        auto k = new QStandardItem(shapes.at(i));
        auto v = new QStandardItem(QString::number(i+3));
        k->setEditable(false);
        model->appendRow({k, v});
    }

    ui->tableView->setModel(model);
    ShapeDelegate *delegate = new ShapeDelegate(this);

    ui->tableView->setItemDelegateForColumn(1, delegate);
    ui->tableView->resizeRowsToContents();
}

MainWindow::~MainWindow()
{
    delete ui;
}
