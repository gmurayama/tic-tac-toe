#include "mainwindow.h"
#include "ui_mainwindow.h"

QVector<QVector<QPushButton *>> board;
int playerTurn = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QVector<QPushButton *> row1(3), row2(3), row3(3);

    row1.push_back(ui->box1);
    row1.push_back(ui->box2);
    row1.push_back(ui->box3);

    row2.push_back(ui->box4);
    row2.push_back(ui->box5);
    row2.push_back(ui->box6);

    row3.push_back(ui->box7);
    row3.push_back(ui->box8);
    row3.push_back(ui->box9);

    board.push_back(row1);
    board.push_back(row2);
    board.push_back(row3);

    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] != nullptr) {
                connect(board[i][j], SIGNAL(clicked()), this, SLOT(mark()));
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mark()
{
    auto buttonSlot = qobject_cast<QPushButton *>(sender());

    playerTurn = ++playerTurn % 2;
    QString mark = playerTurn % 2 == 0 ? "X" : "O";
    ui->labelPlayer->setText(QString("Player: %1").arg(playerTurn + 1));

    buttonSlot->setText(mark);
    buttonSlot->setEnabled(false);
}
