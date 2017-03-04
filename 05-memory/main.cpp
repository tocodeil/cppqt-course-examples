#include <QtWidgets>
#include <QtGui>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget w;

    QVBoxLayout *layout = new QVBoxLayout(&w);
    QLabel *l           = new QLabel("Ouch!", &w);
    QPushButton *b      = new QPushButton("Click Me", &w);

    layout->addWidget(l);
    layout->addWidget(b);

    qDebug() << "Widget w has: " << w.children().size() << " children";
    w.show();

    return a.exec();    
}
