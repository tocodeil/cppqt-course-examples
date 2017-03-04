#include <QtWidgets>
#include <QtGui>
#include <QDebug>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  QDesktopWidget *desktopInfo = QApplication::desktop();
  QRect totalSpace = desktopInfo->availableGeometry();
  QRect goodSizeForLabel = totalSpace.adjusted(50, 50, -50, -50);

  QFont font("Note this", 64);
  QLabel l("Hello World");
  l.setAlignment(Qt::AlignCenter);

  l.setFont(font);
  l.setGeometry(goodSizeForLabel);

  l.show();

  return app.exec();
}
