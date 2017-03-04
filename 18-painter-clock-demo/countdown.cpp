#include "countdown.h"
#include <QPainter>


const int kRes = 10;

Countdown::Countdown(QWidget *parent) :
    QWidget(parent)
{    
    QPalette p = palette();
    p.setColor(QPalette::Window, QColor::fromHsl(32, 62, 100));
    p.setColor(QPalette::WindowText, Qt::black);
    setPalette(p);
}

void Countdown::start()
{
    m_timer.start(kRes, this);
}

void Countdown::stop()
{
    m_timer.stop();
}

QSize Countdown::sizeHint() const
{
    return QSize(100, 100);
}

void Countdown::setCount(int totalCount)
{
    m_totalCount = totalCount;
    m_currentCount = totalCount;
}

void Countdown::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);

    if (--m_currentCount <= 0)
    {
        emit timesUp();
        m_currentCount = m_totalCount;
    }
    update();
}

void Countdown::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter p(this);
    QColor piColor = palette().color(QPalette::Window);
    p.setBrush(piColor);


    int side = qMin(rect().width(), rect().height());
    QRectF rectangle;
    rectangle.setSize(QSizeF(side, side));
    rectangle.moveCenter(rect().center());

    int startAngle = 0 * 16;
    float ratio = (float)m_currentCount / m_totalCount;
    int spanAngle = ratio * 360 * 16;

    p.setPen(Qt::NoPen);
    p.drawPie(rectangle, -startAngle, -spanAngle);

    p.setPen(palette().color(QPalette::WindowText));

    QTextOption opts(Qt::AlignCenter);
    p.drawText(rect(), QString::number(m_currentCount), opts);
}








