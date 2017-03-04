#include "clicker.h"
#include "ui_clicker.h"

Clicker::Clicker(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Clicker)
{
    ui->setupUi(this);
    QObject::connect(ui->btnInc, &QPushButton::clicked,
                     this, &Clicker::handleClick);
}

Clicker::~Clicker()
{
    delete ui;
}

void Clicker::handleClick()
{
    m_clicks++;
    ui->count->setText(QString("%1").arg(m_clicks));

    emit clicksChanged(m_clicks);
}
