#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class SettingsModel;
class QDataWidgetMapper;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void handleDelete();
    void handleAdd();

private:
    Ui::MainWindow *ui;
    SettingsModel *m_model;
    QDataWidgetMapper *m_dataMapper;
};

#endif // MAINWINDOW_H
