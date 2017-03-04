#include "mypainter.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

MyPainter::MyPainter(QWidget *parent) : QWidget(parent)
{

}

QSize MyPainter::sizeHint() const
{
    return QSize(200, 100);
}

void MyPainter::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QColor flagGreen;
    flagGreen.setNamedColor("#006A4E");
    p.fillRect(rect(), flagGreen);

    p.setBrush(circleColor());
    p.drawEllipse(circleRect());
}

void MyPainter::mousePressEvent(QMouseEvent *e)
{
    QPoint clickedOn(e->x(), e->y());
    if (circleRect().contains(clickedOn))
    {
        m_isPressed = true;
        update();
    }
}

void MyPainter::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e);
    if (m_isPressed)
    {
        emit clicked();
        m_isPressed = false;
        update();
    }
}

QRect MyPainter::circleRect()
{
    int side = qMin(rect().height(), rect().width());
    QRect circleRect = QRect(0, 0, side/2, side/2);
    circleRect.moveCenter(QPoint(rect().width() *0.30, rect().center().y()));
    return circleRect;
}

QColor MyPainter::circleColor()
{
    QColor res;
    res.setNamedColor("#F42A41");
    if (!m_isPressed)
    {
        return res;
    }
    else
    {
        return res.lighter(150);
    }

}
