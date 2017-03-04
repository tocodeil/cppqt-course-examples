#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBasicTimer>

namespace Ui {
class MainWindow;
}
class QTimerEvent;
class QMouseEvent;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    virtual void timerEvent(QTimerEvent *event);
    virtual void mousePressEvent(QMouseEvent * event);
    virtual bool eventFilter(QObject *watched, QEvent *event);

    virtual bool event(QEvent *event);

private:
    Ui::MainWindow *ui;
    QBasicTimer m_timer;
    unsigned int m_ticks = 0;
};

#endif // MAINWINDOW_H
