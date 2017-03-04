#include <QtGui>
#include <QtWidgets>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  QLabel l("I see red people");

  l.setStyleSheet("color: red; font-size: 36px");
  l.setAlignment(Qt::AlignCenter);

  l.show();
  return app.exec();
}
