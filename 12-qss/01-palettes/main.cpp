#include <QtGui>
#include <QtWidgets>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  QLabel l("I see red people");

  QPalette p = l.palette();
  p.setColor(QPalette::WindowText, Qt::red);
  l.setPalette(p);

  l.show();
  return app.exec();
}
