#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <QWidget>
#include <QBasicTimer>

class Countdown : public QWidget
{
    Q_OBJECT
public:
    explicit Countdown(QWidget *parent = 0);
    virtual QSize sizeHint() const;

    void setCount(int totalCount);

signals:
    void timesUp();

public slots:
    void start();
    void stop();

protected:
    virtual void timerEvent(QTimerEvent *e);
    virtual void paintEvent(QPaintEvent *e);

private:
    QBasicTimer m_timer;
    int m_currentCount = 1;
    int m_totalCount = 1;
};

#endif // COUNTDOWN_H
