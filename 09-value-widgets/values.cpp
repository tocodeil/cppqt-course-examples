#include "values.h"
#include "ui_values.h"
#include <functional>


Values::Values(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Values)
{
    ui->setupUi(this);

    QObject::connect(ui->slider, &QSlider::valueChanged,
                     ui->spinbox, &QSpinBox::setValue);
    QObject::connect(ui->spinbox, SIGNAL(valueChanged(int)),
                     ui->slider, SLOT(setValue(int)));

    QObject::connect(ui->add5, &QPushButton::clicked,
                     std::bind(&Values::addX, this, 5));
    QObject::connect(ui->add10, &QPushButton::clicked,
                     std::bind(&Values::addX, this, 10));

}

Values::~Values()
{
    delete ui;
}

void Values::addX(int val)
{
    ui->progress->setValue(ui->progress->value() + val);
}
