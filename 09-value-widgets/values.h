#ifndef VALUES_H
#define VALUES_H

#include <QWidget>

namespace Ui {
class Values;
}

class Values : public QWidget
{
    Q_OBJECT

public:
    explicit Values(QWidget *parent = 0);
    ~Values();

public:
    void addX(int val);

private:
    Ui::Values *ui;
};

#endif // VALUES_H
