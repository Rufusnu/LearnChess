#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "piece.h"
#include <vector>
#include <QMatrix>
#include <QObject>
using namespace std;


class chessBoard : public QObject
{
    Q_OBJECT

private:
    Position matrix[8][8];
    QWidget* widgetTable;
    QGridLayout* layout;
    QSignalMapper* mapper;
    Piece* currentPiece;
    QIcon* pieceIcon;

    void clearTable();
    unsigned int randomNbr();
    void colorPossibleMoves(vector<Position> positions);

    QElapsedTimer timer;
    unsigned int numberOfMoves;

public:
    chessBoard();
    void generateTableWith(Piece* piece);

    QWidget* getTable();
    unsigned int getNumberOfMoves() const;
public slots:
    void movePiece(int xy);
    void startTimer();
};

#endif // CHESSBOARD_H
