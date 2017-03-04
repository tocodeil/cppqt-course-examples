#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class WaitDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void showQtModalDialog();
    void showCustomModalDialog();
    void showCustomModelessDialog();

private:
    Ui::MainWindow *ui;
    WaitDialog *modelessWaitDialog;
};

#endif // MAINWINDOW_H
