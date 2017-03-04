#ifndef CLICKER_H
#define CLICKER_H

#include <QWidget>

namespace Ui {
class Clicker;
}

class Clicker : public QWidget
{
    Q_OBJECT

public:
    explicit Clicker(QWidget *parent = 0);
    ~Clicker();

signals:
    void clicksChanged(int newValue);

private:
    void handleClick();

private:
    Ui::Clicker *ui;
    unsigned long m_clicks = 0;
};

#endif // CLICKER_H
