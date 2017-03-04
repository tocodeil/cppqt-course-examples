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
                     ui->actionNew_Game, &QAction::triggered);

    QObject::connect(ui->actionNew_Game, &QAction::triggered,
                     this, &MainWindow::newGame);

    QObject::connect(ui->actionShow_Game_List, &QAction::triggered,
                     std::bind(&QDockWidget::setVisible, ui->dockWidget, true));

    QObject::connect(ui->dockWidget, &QDockWidget::visibilityChanged,
                     [&](bool visible) { ui->actionShow_Game_List->setEnabled(!visible); });

    ui->actionNew_Game->setShortcut(QKeySequence::New);
    ui->statusBar->addWidget(new QLabel("Current Player: X"));
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

    setCurrentPlayer(currentPlayer == "X" ? "O" : "X");
}

void MainWindow::newGame()
{
    setCurrentPlayer("X");
    QList<QPushButton *> buttons = ui->board->findChildren<QPushButton *>();
    for (int i=0; i < kRows * kCols; i++)
    {
        board[i] = QString();
        buttons[i]->setText(QString());
    }
}

void MainWindow::setCurrentPlayer(QString player)
{
    currentPlayer = player;
    ui->label->setText("Current Player: " + currentPlayer);
    QLabel *statusLabel = ui->statusBar->findChild<QLabel *>();
    statusLabel->setText("Current Player: " + currentPlayer);
}








