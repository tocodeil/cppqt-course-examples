#include <QtGui>
#include <QtWidgets>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  QWidget w;
  QGridLayout *layout  = new QGridLayout(&w);

  QListWidget *selectFamily = new QListWidget();
  selectFamily->addItems({ "Arial", "Helvetica", "David", "Miriam" });
  
  QListWidget *selectSize = new QListWidget();
  selectSize->addItems({ "18px", "24px", "36px", "48px", "72px" });
  
  layout->addWidget(new QLabel("Font Family"), 0, 0);
  layout->addWidget(selectFamily, 1, 0);

  layout->addWidget(new QLabel("Font Size"), 0, 2);
  layout->addWidget(selectSize, 1, 2);

  layout->setColumnMinimumWidth(1, 10);

  w.show();
  return app.exec();
}
