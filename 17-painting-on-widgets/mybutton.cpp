#include "mybutton.h"
#include <QPainter>

MyButton::MyButton(QWidget *parent) : QWidget(parent)
{

}

void MyButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    QRect area = rect().adjusted(20, 20, -20, 20);
    QColor bg;

    if (!m_isPressed)
    {
        bg.setNamedColor("#F3AE55");
        p.fillRect(area, bg);
    }
    else
    {
        bg.setNamedColor("#A05E11");
        p.fillRect(area, bg);
    }
}

void MyButton::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e);
    m_isPressed = true;
    update();
}

void MyButton::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e);
    m_isPressed = false;
    emit clicked();

    update();
}

