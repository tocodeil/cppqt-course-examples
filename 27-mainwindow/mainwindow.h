#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void handleClick(int index, QPushButton *target);
    void newGame();
    void setCurrentPlayer(QString player);

private:
    Ui::MainWindow *ui;
    QString board[9];
    QString currentPlayer = "X";
};

#endif // MAINWINDOW_H
