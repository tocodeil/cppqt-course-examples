#include "mainwindow.h"
#include <QApplication>
#include <QtGui>
#include <QtWidgets>

auto showMultiplicationTable(int argc, char **argv)
{
    QApplication a(argc, argv);
    QStandardItemModel model;
    for (auto i=1; i <= 10; i++)
    {
        QList<QStandardItem *> row;
        for (auto j=1; j <= 10; j++)
        {
            auto item = new QStandardItem(QString::number(i*j));
            item->setEditable(false);
            if ((i*j) % 3 == 0)
            {
                item->setData(QVariant::fromValue<QColor>(Qt::yellow), Qt::BackgroundRole);
            }
            row << item;
        }
        model.appendRow(row);
    }

    QTableView tv;
    tv.setModel(&model);
    tv.show();
    return a.exec();
}

auto showFilesystemModelView(int argc, char **argv)
{
    QApplication a(argc, argv);
    QFileSystemModel fs;
    fs.setRootPath(QDir::homePath());

    QTableView tv;
    tv.setModel(&fs);
    tv.setRootIndex(fs.index(QDir::homePath()));
    tv.show();

    QListView lv;
    lv.setModel(&fs);
    lv.setRootIndex(fs.index(QDir::homePath()));
    lv.show();

    QTreeView rv;
    rv.setModel(&fs);
    rv.setRootIndex(fs.index(QDir::homePath()));
    rv.show();
    return a.exec();
}

int main(int argc, char *argv[])
{
    showMultiplicationTable(argc, argv);
}
