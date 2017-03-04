#include <QtGui>
#include <QtWidgets>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  QWidget w;
  QVBoxLayout *layout = new QVBoxLayout(&w);
  layout->addWidget(new QLabel("Line 1"));
  layout->addWidget(new QLabel("Line 2"));

  QHBoxLayout *r3 = new QHBoxLayout();
  layout->addLayout(r3);
  r3->addWidget(new QLabel("Line 3"));
  r3->addWidget(new QPushButton("Click Here"));

  w.show();
  return app.exec();
}
