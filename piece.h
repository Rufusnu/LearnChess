#ifndef PIECE_H
#define PIECE_H
#include "vector"
#include "QtWidgets"
using namespace std;

class Position;

// *** Abstract Base class Piece ***
class Piece
{
public:
    Piece();
    virtual ~Piece();
    virtual vector<Position> getPossibleMoves(Position pos) = 0;
};
// *** END-Abstract Base class Piece ***


// *** Position ***
class Position
{
private:
    unsigned int xPoint;
    unsigned int yPoint;
    bool possible;
    Piece* piece;
    bool star;
public:
    Position();
    Position(unsigned int, unsigned int, Piece*);
    ~Position();
    Position& operator=(const Position &);
    unsigned int x() const;
    unsigned int y() const;
    Piece* getPiece() const;
    void setPiece(Piece*);
    bool isViablePosition() const;
    void setPossible(bool);
    bool isStar() const;
    void setIsStar(bool);

};
// *** END-Position ***


// *** Derived Piece Classes ***
class Pawn : public Piece
{
public:
    vector<Position> getPossibleMoves(Position pos);
};

class King : public Piece
{
public:
    vector<Position> getPossibleMoves(Position pos);
};

class Queen : public Piece
{
public:
    vector<Position> getPossibleMoves(Position pos);
};

class Bishop : public Piece
{
public:
    vector<Position> getPossibleMoves(Position pos);
};

class Knight : public Piece
{
public:
    vector<Position> getPossibleMoves(Position pos);
};

class Rook : public Piece
{
public:
    vector<Position> getPossibleMoves(Position pos);
};
// *** END-Derived pieces ***

#endif // PIECE_H
