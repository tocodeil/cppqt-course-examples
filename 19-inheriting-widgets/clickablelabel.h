#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>

class ClickableLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ClickableLabel(QWidget *parent = 0);
    explicit ClickableLabel(const QString &text, QWidget *parent = 0);

protected:
    void mouseReleaseEvent(QMouseEvent *ev);

signals:
    void clicked();

};

#endif // CLICKABLELABEL_H
