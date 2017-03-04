#ifndef MYPAINTER_H
#define MYPAINTER_H

#include <QWidget>

class MyPainter : public QWidget
{
    Q_OBJECT
public:
    explicit MyPainter(QWidget *parent = 0);
    QSize sizeHint() const;

signals:
    void clicked();

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);


private:
    QRect circleRect();
    QColor circleColor();

private:
    bool m_isPressed = false;
};

#endif // MYPAINTER_H
