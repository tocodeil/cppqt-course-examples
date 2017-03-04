#include <QtGui>
#include <QtWidgets>
#include <QtCore>

void loadStyleSheets(QString styleFile)
{
  QFile f(styleFile);
  if (f.open(QIODevice::ReadOnly)) 
  {
    QString contents(f.readAll());
    qApp->setStyleSheet(contents);
    f.close();
  }
  else
  {
    qDebug() << "Failed to open file: " << styleFile;
  }
}

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  if (argc > 1)
  {
    loadStyleSheets(app.arguments().at(1));
  }

  QLabel l("I see red people");

  l.show();
  return app.exec();
}
