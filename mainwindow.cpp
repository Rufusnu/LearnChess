
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QVBoxLayout"
#include "QHBoxLayout"
#include "QFrame"
#include "QPushButton"
#include "iostream"
#include <cstdlib>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->createGUI();
}

void MainWindow::createGUI()
{
    this->setWindowTitle("Learn Chess");
    this->setMinimumSize(QSize(480, 480));
    this->setMaximumSize(QSize(480, 480));
    this->setStyleSheet("background-color: darkgray");
    QWidget *centralW = createMenuWidget();
    this->setCentralWidget(centralW);
}

void MainWindow::quitGUI()
{
    MainWindow::close();
}

// *** MAIN MENU ***
QWidget* MainWindow::createMenuWidget()
{
    QWidget* widget=new QWidget(this);

    QWidget* menuProductW = createMenuWidgetElements();
    QVBoxLayout* vBoxLayout = new QVBoxLayout;

    vBoxLayout->addWidget(menuProductW);

    QFrame *line =  new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    vBoxLayout->addWidget(line);

    widget->setLayout(vBoxLayout);

    return widget;
}

QWidget* MainWindow::createMenuWidgetElements()
{
    QWidget* widget = new QWidget(this);

    QVBoxLayout *vBox = new QVBoxLayout(this);
    QLabel *title = new QLabel("Chess");
    QPushButton *buttonPlay = new QPushButton("Learn to Play!",this);
    QPushButton *buttonQuit = new QPushButton("Quit",this);
    QFrame *line1 =  new QFrame(this);
    line1->setFrameShape(QFrame::HLine);
    line1->setFrameShadow(QFrame::Sunken);
    QFrame *line2 =  new QFrame(this);
    line2->setFrameShape(QFrame::HLine);
    line2->setFrameShadow(QFrame::Sunken);

    title->setStyleSheet("font-size: 60px; font-weight: bold; color: rgb(0,123,144)");
    buttonPlay->setStyleSheet("QPushButton:hover{font-size: 40px; color: rgb(61,165,202); background-color: rgb(196,240,255)}"
                              "QPushButton:!hover{font-size: 40px; color: rgb(54,145,177); background-color: rgb(119,186,209)}");
    buttonQuit->setStyleSheet("QPushButton:hover{font-size: 30px; color: rgb(61,165,202); background-color: rgb(196,240,255)}"
                              "QPushButton:!hover{font-size: 30px; color: rgb(54,145,177); background-color: rgb(119,186,209)}");

    buttonPlay->setFixedSize(400,160);
    line1->setFixedWidth(200);
    line2->setFixedWidth(450);
    buttonQuit->setFixedSize(280,100);

    vBox->addWidget(title);
    vBox->itemAt(0)->setAlignment(Qt::AlignCenter);
    vBox->addWidget(line1);
    vBox->itemAt(1)->setAlignment(Qt::AlignCenter);
    vBox->addWidget(buttonPlay);
    vBox->itemAt(2)->setAlignment(Qt::AlignCenter);
    vBox->addWidget(line2);
    vBox->itemAt(3)->setAlignment(Qt::AlignCenter);
    vBox->addWidget(buttonQuit);
    vBox->itemAt(4)->setAlignment(Qt::AlignCenter);

    vBox->setAlignment(Qt::AlignCenter);


    widget->setLayout(vBox);

    connect(buttonQuit, &QPushButton:: pressed, this, &MainWindow:: quitGUI);
    connect(buttonPlay, &QPushButton:: pressed, this, &MainWindow:: createMenuSelectPiece);

    return widget;
}
// *** END_MAIN MENU ***


// *** SELECT PIECE MENU ***
void MainWindow::createMenuSelectPiece()
{
    QWidget* widget=new QWidget(this);

    QWidget* menuSelectW = createMenuSelectPieceElements();
    QVBoxLayout* vBoxLayout = new QVBoxLayout;

    vBoxLayout->addWidget(menuSelectW);

    widget->setLayout(vBoxLayout);
    this->setCentralWidget(widget);
}

QWidget* MainWindow::createMenuSelectPieceElements()
{
    QWidget* widget = new QWidget(this);

    QGridLayout *grid = new QGridLayout(this);
    QVBoxLayout *vBox = new QVBoxLayout(this);
    QPushButton *buttonPawn = new QPushButton("Pawn!",this);
    QPushButton *buttonKing = new QPushButton("King!",this);
    QPushButton *buttonQueen = new QPushButton("Queen!",this);
    QPushButton *buttonBishop = new QPushButton("Bishop!",this);
    QPushButton *buttonKnight = new QPushButton("Knight!",this);
    QPushButton *buttonRook = new QPushButton("Rook!",this);
    QPushButton *buttonBack = new QPushButton("<- Back <-",this);

    setPredifinedStyle(buttonPawn);
    setPredifinedStyle(buttonKing);
    setPredifinedStyle(buttonQueen);
    setPredifinedStyle(buttonBishop);
    setPredifinedStyle(buttonKnight);
    setPredifinedStyle(buttonRook);
    setPredifinedStyle(buttonBack);

    buttonPawn->setFixedHeight(90);
    buttonKing->setFixedHeight(90);
    buttonQueen->setFixedHeight(90);
    buttonBishop->setFixedHeight(90);
    buttonKnight->setFixedHeight(90);
    buttonRook->setFixedHeight(90);

    buttonBack->setFixedHeight(50);

    QFrame *line =  new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    grid->addWidget(buttonPawn,1,1);
    grid->addWidget(buttonKing,2,1);
    grid->addWidget(buttonQueen,3,1);
    grid->addWidget(buttonBishop,1,2);
    grid->addWidget(buttonKnight,2,2);
    grid->addWidget(buttonRook,3,2);
    vBox->addLayout(grid);
    vBox->addWidget(line);
    vBox->addWidget(buttonBack);

    widget->setLayout(vBox);

    connect(buttonBack, &QPushButton:: pressed, this, &MainWindow:: createGUI);
    connect(buttonPawn, &QPushButton:: pressed, this, &MainWindow:: createChessPawn);
    connect(buttonKing, &QPushButton:: pressed, this, &MainWindow:: createChessKing);
    connect(buttonQueen, &QPushButton:: pressed, this, &MainWindow:: createChessQueen);
    connect(buttonBishop, &QPushButton:: pressed, this, &MainWindow:: createChessBishop);
    connect(buttonKnight, &QPushButton:: pressed, this, &MainWindow:: createChessKnight);
    connect(buttonRook, &QPushButton:: pressed, this, &MainWindow:: createChessRook);

    return widget;
}

void MainWindow::createChessPawn()
{
    QWidget* widget = new QWidget(this);
    Piece* pawn = new Pawn();
    widget = createTable(pawn);
    this->chessTable->startTimer();
    this->setCentralWidget(widget);
}

void MainWindow::createChessKing()
{
    QWidget* widget = new QWidget(this);
    Piece* king = new King();
    widget = createTable(king);
    this->chessTable->startTimer();
    this->setCentralWidget(widget);
}

void MainWindow::createChessQueen()
{
    QWidget* widget = new QWidget(this);
    Piece* queen = new Queen();
    widget = createTable(queen);
    this->chessTable->startTimer();
    this->setCentralWidget(widget);
}

void MainWindow::createChessBishop()
{
    QWidget* widget = new QWidget(this);
    Piece* bishop = new Bishop();
    widget = createTable(bishop);
    this->chessTable->startTimer();
    this->setCentralWidget(widget);
}

void MainWindow::createChessKnight()
{
    QWidget* widget = new QWidget(this);
    Piece* knight = new Knight();
    widget = createTable(knight);
    this->chessTable->startTimer();
    this->setCentralWidget(widget);
}

void MainWindow::createChessRook()
{
    QWidget* widget = new QWidget(this);
    Piece* rook = new Rook();
    widget = createTable(rook);
    this->chessTable->startTimer();
    this->setCentralWidget(widget);
}
// *** END_SELECT PIECE MENU ***

QWidget* MainWindow::createTable(Piece *piece)
{
    this->chessTable = new chessBoard();
    this->chessTable->generateTableWith(piece);
    this->setStyleSheet("background-color: lightgray");
    return this->chessTable->getTable();
}

void MainWindow::setPredifinedStyle(QPushButton* button)
{
    button->setStyleSheet("QPushButton:hover{font-size: 20px; color: rgb(61,165,202); background-color: rgb(196,240,255)}"
                          "QPushButton:!hover{font-size: 20px; color: rgb(28,125,160); background-color: rgb(119,186,209)}");
}
