#include "piece.h"


Piece::Piece() {}

Piece::~Piece() {}


// *** Position ***
Position::Position()
{
    this->xPoint = 0;
    this->yPoint = 0;
    this->possible = false;
    this->piece = nullptr;
    this->star = false;
}
Position::~Position() {}

Position::Position(unsigned int newX, unsigned int newY, Piece *newPiece)
{
    this->xPoint = newX;
    this->yPoint = newY;
    *this->piece = *newPiece;
}

unsigned int Position::x() const
{
    return this->xPoint;
}

unsigned int Position::y() const
{
    return this->yPoint;
}

Piece* Position::getPiece() const
{
    return this->piece;
}

void Position::setPiece(Piece* target)
{
    *this->piece = *target;
}

Position& Position::operator=(const Position &target)
{
    this->xPoint = target.xPoint;
    this->yPoint = target.yPoint;
    this->piece = target.piece;
    return *this;
}

bool Position::isViablePosition() const
{
    return this->possible;
}

void Position::setPossible(bool state)
{
    this->possible = state;
}

bool Position::isStar() const
{
    return this->star;
}

void Position::setIsStar(bool is)
{
    this->star = is;
}
// *** END-Position ***



// Moves of derived pieces
vector<Position> Pawn::getPossibleMoves(Position pos)
{
    vector<Position> viablePositions;
    if (pos.x() > 0) // 1UP
    {
        Position oneUp(pos.x() - 1, pos.y(), nullptr);
        viablePositions.push_back(oneUp);
    }

    return viablePositions;
}

vector<Position> King::getPossibleMoves(Position pos)
{
    vector<Position> viablePositions;
    if (pos.y() > 0) // 1UP
    {
        Position oneUp(pos.x(), pos.y() - 1, nullptr);
        viablePositions.push_back(oneUp);
    }
    if (pos.y() < 7) // 1DOWN
    {
        Position oneDown(pos.x(), pos.y() + 1, nullptr);
        viablePositions.push_back(oneDown);
    }
    if (pos.x() > 0) // 1LEFT
    {
        Position oneLeft(pos.x() - 1, pos.y(), nullptr);
        viablePositions.push_back(oneLeft);
    }
    if (pos.x() < 7) // 1RIGHT
    {
        Position oneRight(pos.x() + 1, pos.y(), nullptr);
        viablePositions.push_back(oneRight);
    }
    if(pos.x() > 0 && pos.y() > 0) // UP-LEFT
    {
        Position oneUpLeft(pos.x() - 1, pos.y() - 1, nullptr);
        viablePositions.push_back(oneUpLeft);
    }
    if(pos.x() < 7 && pos.y() > 0) // UP-RIGHT
    {
        Position oneUpRight(pos.x() + 1, pos.y() - 1, nullptr);
        viablePositions.push_back(oneUpRight);
    }
    if(pos.x() > 0 && pos.y() < 7) // DOWN-LEFT
    {
        Position oneDownLeft(pos.x() - 1, pos.y() + 1, nullptr);
        viablePositions.push_back(oneDownLeft);
    }
    if(pos.x() < 7 && pos.y() < 7) // DOWN-RIGHT
    {
        Position oneDownRight(pos.x() + 1, pos.y() + 1, nullptr);
        viablePositions.push_back(oneDownRight);
    }

    return viablePositions;
}

vector<Position> Queen::getPossibleMoves(Position pos)
{
    vector<Position> viablePositions;

    // ROOK
    unsigned int x = pos.x(), y = pos.y();
    while (y > 0) // 1UP
    {
        y--;
        Position oneUp(x, y, nullptr);
        viablePositions.push_back(oneUp);
    }

    x = pos.x(), y = pos.y(); // RESET
    while (y < 7) // 1DOWN
    {
        y++;
        Position oneDown(x, y, nullptr);
        viablePositions.push_back(oneDown);
    }

    x = pos.x(), y = pos.y(); // RESET
    while (x > 0) // 1LEFT
    {
        x--;
        Position oneLeft(x, y, nullptr);
        viablePositions.push_back(oneLeft);
    }

    x = pos.x(), y = pos.y(); // RESET
    while (x < 7) // 1RIGHT
    {
        x++;
        Position oneUp(x, y, nullptr);
        viablePositions.push_back(oneUp);
    }

    // BISHOP
    x = pos.x(), y = pos.y();
    while(x > 0 && y > 0) // UP-LEFT
    {
        x--;
        y--;
        Position oneUp(x, y, nullptr);
        viablePositions.push_back(oneUp);
    }

    x = pos.x(), y = pos.y(); // RESET
    while(x < 7 && y > 0) // UP-RIGHT
    {
        x++;
        y--;
        Position oneUp(x, y, nullptr);
        viablePositions.push_back(oneUp);
    }

    x = pos.x(), y = pos.y(); // RESET
    while(x > 0 && y < 7) // DOWN-LEFT
    {
        x--;
        y++;
        Position oneUp(x, y, nullptr);
        viablePositions.push_back(oneUp);
    }

    x = pos.x(), y = pos.y(); // RESET
    while(x < 7 && y < 7) // DOWN-RIGHT
    {
        x++;
        y++;
        Position oneUp(x, y, nullptr);
        viablePositions.push_back(oneUp);
    }

    return viablePositions;
}

vector<Position> Bishop::getPossibleMoves(Position pos)
{
    vector<Position> viablePositions;

    unsigned int x = pos.x(), y = pos.y();
    while(x > 0 && y > 0) // UP-LEFT
    {
        x--;
        y--;
        Position oneUp(x, y, nullptr);
        viablePositions.push_back(oneUp);
    }

    x = pos.x(), y = pos.y(); // RESET
    while(x < 7 && y > 0) // UP-RIGHT
    {
        x++;
        y--;
        Position oneUp(x, y, nullptr);
        viablePositions.push_back(oneUp);
    }

    x = pos.x(), y = pos.y(); // RESET
    while(x > 0 && y < 7) // DOWN-LEFT
    {
        x--;
        y++;
        Position oneUp(x, y, nullptr);
        viablePositions.push_back(oneUp);
    }

    x = pos.x(), y = pos.y(); // RESET
    while(x < 7 && y < 7) // DOWN-RIGHT
    {
        x++;
        y++;
        Position oneUp(x, y, nullptr);
        viablePositions.push_back(oneUp);
    }
    return viablePositions;
}

vector<Position> Knight::getPossibleMoves(Position pos)
{
    vector<Position> viablePositions;

    if (pos.x() > 1 && pos.y() > 0) // UP-LEFT
    {
        Position oneUpLeft(pos.x() - 2, pos.y() - 1, nullptr);
        viablePositions.push_back(oneUpLeft);
    }
    if (pos.x() > 1 && pos.y() < 7) // UP-RIGHT
    {
        Position oneUpRight(pos.x() - 2, pos.y() + 1, nullptr);
        viablePositions.push_back(oneUpRight);
    }
    if (pos.x() > 0 && pos.y() < 6) // RIGHT-UP
    {
        Position oneRightUp(pos.x() - 1, pos.y() + 2, nullptr);
        viablePositions.push_back(oneRightUp);
    }
    if (pos.x() < 7 && pos.y() < 6) // RIGHT-DOWN
    {
        Position oneRightDown(pos.x() + 1, pos.y() + 2, nullptr);
        viablePositions.push_back(oneRightDown);
    }
    if (pos.x() < 6 && pos.y() < 7) // DOWN-RIGHT
    {
        Position oneDownRight(pos.x() + 2, pos.y() + 1, nullptr);
        viablePositions.push_back(oneDownRight);
    }
    if (pos.x() < 6 && pos.y() > 0) // DOWN-LEFT
    {
        Position oneDownLeft(pos.x() + 2, pos.y() - 1, nullptr);
        viablePositions.push_back(oneDownLeft);
    }
    if (pos.x() < 7 && pos.y() > 1) // LEFT-DOWN
    {
        Position oneDownLeft(pos.x() + 1, pos.y() - 2, nullptr);
        viablePositions.push_back(oneDownLeft);
    }
    if (pos.x() > 0 && pos.y() > 1) // LEFT-UP
    {
        Position oneDownLeft(pos.x() - 1, pos.y() - 2, nullptr);
        viablePositions.push_back(oneDownLeft);
    }
    return viablePositions;
}

vector<Position> Rook::getPossibleMoves(Position pos)
{
    vector<Position> viablePositions;

    unsigned int x = pos.x(), y = pos.y();
    while (y > 0) // 1UP
    {
        y--;
        Position oneUp(x, y, nullptr);
        viablePositions.push_back(oneUp);
    }

    x = pos.x(), y = pos.y(); // RESET
    while (y < 7) // 1DOWN
    {
        y++;
        Position oneDown(x, y, nullptr);
        viablePositions.push_back(oneDown);
    }

    x = pos.x(), y = pos.y(); // RESET
    while (x > 0) // 1LEFT
    {
        x--;
        Position oneLeft(x, y, nullptr);
        viablePositions.push_back(oneLeft);
    }

    x = pos.x(), y = pos.y(); // RESET
    while (x < 7) // 1RIGHT
    {
        x++;
        Position oneUp(x, y, nullptr);
        viablePositions.push_back(oneUp);
    }

    return viablePositions;
}
