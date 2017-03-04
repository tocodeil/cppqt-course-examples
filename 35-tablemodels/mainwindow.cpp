#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsmodel.h"
#include <QDebug>
#include <QDataWidgetMapper>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_model = new SettingsModel(this);
    m_dataMapper = new QDataWidgetMapper(this);
    m_dataMapper->setModel(m_model);
    m_dataMapper->addMapping(ui->eKey, 0);
    m_dataMapper->addMapping(ui->eValue, 1);
    m_dataMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    ui->tableView->setModel(m_model);
    ui->tableView->resizeColumnsToContents();

    QObject::connect(ui->btnDelete, &QPushButton::clicked,
                     this, &MainWindow::handleDelete);

    QObject::connect(ui->btnAdd, &QPushButton::clicked,
                     this, &MainWindow::handleAdd);

    QObject::connect(ui->tableView->selectionModel(), &QItemSelectionModel::currentRowChanged,
                     m_dataMapper, &QDataWidgetMapper::setCurrentModelIndex);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleDelete()
{
    QModelIndexList rowsToDelete = ui->tableView->selectionModel()->selectedRows();
    for (auto index : rowsToDelete)
    {
        m_model->removeRow(index.row());
    }
}

void MainWindow::handleAdd()
{
    QString key = ui->eKey->text();
    QString val = ui->eValue->text();
    if (m_model->addSetting(key, val))
    {
        ui->eKey->setText(QString());
        ui->eValue->setText(QString());
    }
}








