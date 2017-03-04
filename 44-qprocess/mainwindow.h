#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

namespace Ui {
class MainWindow;
}


class QErrorMessage;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void handleRefresh();
    void handleReadyRead();
    void handleProcessFinished();
    void handleError(QProcess::ProcessError error);

private:
    Ui::MainWindow *ui;
    QProcess *proc;
    QErrorMessage *errorDialog;
};

#endif // MAINWINDOW_H
