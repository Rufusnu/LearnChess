#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "piece.h"
#include <QMainWindow>
#include "chessboard.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void createGUI();
    void quitGUI();

    void createMenuSelectPiece();
    void createChessPawn();
    void createChessKing();
    void createChessQueen();
    void createChessBishop();
    void createChessKnight();
    void createChessRook();

private:
    QWidget* createMenuWidget();
    QWidget* createMenuWidgetElements();

    QWidget* createMenuSelectPieceElements();

    chessBoard* chessTable;

    QWidget* createTable(Piece* piece);

    void setPredifinedStyle(QPushButton* button);
public:
    MainWindow(QWidget *parent = nullptr);

};
#endif // MAINWINDOW_H
