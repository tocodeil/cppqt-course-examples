#ifndef WAITDIALOG_H
#define WAITDIALOG_H

#include <QDialog>
#include <QBasicTimer>

namespace Ui {
class WaitDialog;
}

class WaitDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WaitDialog(QWidget *parent = 0);
    ~WaitDialog();

    void reset();

protected:
    virtual void timerEvent(QTimerEvent *event);



private:
    Ui::WaitDialog *ui;
    QBasicTimer timer;
    int secondsLeft = 5;
};

#endif // WAITDIALOG_H
