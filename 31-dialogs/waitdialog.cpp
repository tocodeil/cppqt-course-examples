#include "waitdialog.h"
#include "ui_waitdialog.h"

WaitDialog::WaitDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WaitDialog)
{
    ui->setupUi(this);
    QObject::connect(ui->btnCancel, &QPushButton::clicked,
                     this, &WaitDialog::reject);
    reset();
}

WaitDialog::~WaitDialog()
{
    delete ui;
}

void WaitDialog::reset()
{
    ui->progressBar->setValue(0);
    secondsLeft = 5;
    timer.start(1000, this);
}

void WaitDialog::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    float tick = (ui->progressBar->maximum() - ui->progressBar->minimum()) / 5;
    ui->progressBar->setValue(ui->progressBar->value() + tick);
    if (--secondsLeft <= 0)
    {
        timer.stop();
        accept();
    }
}
