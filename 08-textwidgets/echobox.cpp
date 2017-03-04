#include "echobox.h"
#include "ui_echobox.h"

EchoBox::EchoBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EchoBox)
{
    ui->setupUi(this);
    QObject::connect(ui->send, &QPushButton::clicked,
                     this, &EchoBox::addMessage);

    QObject::connect(ui->msg, &QLineEdit::returnPressed,
                     this, &EchoBox::addMessage);
}

EchoBox::~EchoBox()
{
    delete ui;
}

void EchoBox::addMessage()
{
    ui->log->append(QString("You said: %1").arg(ui->msg->text()));
    ui->msg->clear();
}
