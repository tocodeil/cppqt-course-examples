#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class ImageConverter;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void selectFiles();
    void convert();

    void handleConvertDone(QString fileName);

private:
    Ui::MainWindow *ui;
    ImageConverter *m_converter;
};

#endif // MAINWINDOW_H
