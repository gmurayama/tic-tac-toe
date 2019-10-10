#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>

bool gameWasWon();

QVector<QVector<QPushButton *>> board;
int playerTurn = 0;
int markedSlots = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QVector<QPushButton *> row1, row2, row3;

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
            connect(board[i][j], SIGNAL(clicked()), this, SLOT(mark()));
        }
    }

    connect(ui->buttonReset, SIGNAL(clicked()), this, SLOT(resetGame()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mark()
{
    auto buttonSlot = qobject_cast<QPushButton *>(sender());

    QString mark = playerTurn % 2 == 0 ? "X" : "O";

    buttonSlot->setText(mark);
    buttonSlot->setEnabled(false);

    if (gameWasWon()) {
        ui->labelWinner->setText(QString("Player %1 has won!").arg(playerTurn + 1));

        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board.size(); j++) {
                board[i][j]->setEnabled(false);
            }
        }
    }
    else {
        playerTurn = ++playerTurn % 2;
        markedSlots++;

        if (markedSlots == 9) {
            ui->labelWinner->setText(QString("Tied game"));
            return;
        }
    }

    ui->labelPlayer->setText(QString("Player: %1").arg(playerTurn + 1));
}

void MainWindow::resetGame() {
    playerTurn = 0;
    markedSlots = 0;
    ui->labelPlayer->setText("Player: 1");
    ui->labelWinner->setText("");

    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.size(); j++) {
            board[i][j]->setText("");
            board[i][j]->setEnabled(true);
        }
    }
}

bool gameWasWon()
{
    for (int i = 0; i < board.size() - 1; i++) {
        int rowMatches = 0, colMatches = 0;

        for (int j = 0; j < board.size() - 1; j++) {
            if (board[i][j]->text() != "" && board[i][j]->text() == board[i][j + 1]->text()) {
                rowMatches++;
            }

            if (board[j][i]->text() != "" && board[j][i]->text() == board[j + 1][i]->text()) {
                colMatches++;
            }
        }

        qDebug() << "rowMatches: " << rowMatches << " colMatches: " << colMatches;

        if (rowMatches == 2 || colMatches == 2) {
            return true;
        }
    }

    if (board[1][1]->text() != "" &&
        ((board[0][0]->text() == board[1][1]->text() && board[1][1]->text() == board[2][2]->text()) ||
         (board[2][0]->text() == board[1][1]->text() && board[1][1]->text() == board[0][2]->text()))
        ) {
        return true;
    }

    return false;
}
