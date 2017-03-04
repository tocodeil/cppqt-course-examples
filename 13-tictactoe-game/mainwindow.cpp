#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <functional>

const int kRows = 3;
const int kCols = 3;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGridLayout *boardLayout = new QGridLayout(ui->board);

    for (int i=0; i < kRows; i++) {
        for (int j=0; j < kCols; j++) {
            QPushButton *btn = new QPushButton();
            btn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
            boardLayout->addWidget(btn, i, j);
            QObject::connect(btn, &QPushButton::clicked,
                             std::bind(&MainWindow::handleClick, this, (kRows*i) + j, btn));
        }
    }
    QObject::connect(ui->btnNewGame, &QPushButton::clicked,
                     this, &MainWindow::newGame);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::handleClick(int index, QPushButton *target)
{
    if (board[index] != QString()) {
        // can't play in a non empty square
        return;
    }
    target->setText(currentPlayer);
    board[index] = currentPlayer;

    currentPlayer = (currentPlayer == "X" ? "O" : "X");
    ui->label->setText("Current Player: " + currentPlayer);
}

void MainWindow::newGame()
{
    currentPlayer = "X";
    ui->label->setText("Current Player: " + currentPlayer);
    QList<QPushButton *> buttons = ui->board->findChildren<QPushButton *>();
    for (int i=0; i < kRows * kCols; i++)
    {
        board[i] = QString();
        buttons[i]->setText(QString());
    }
}








