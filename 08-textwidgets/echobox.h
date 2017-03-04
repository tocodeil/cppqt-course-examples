#ifndef ECHOBOX_H
#define ECHOBOX_H

#include <QWidget>

namespace Ui {
class EchoBox;
}

class EchoBox : public QWidget
{
    Q_OBJECT

public:
    explicit EchoBox(QWidget *parent = 0);
    ~EchoBox();

private:
    void addMessage();

private:
    Ui::EchoBox *ui;
};

#endif // ECHOBOX_H
