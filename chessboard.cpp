#include "chessboard.h"
#include "QSignalMapper"
#include <random>
#include "iostream"

chessBoard::chessBoard()
{
    this->layout = new QGridLayout();
    this->layout->setSpacing(0);
    this->layout->setMargin(0);
    this->numberOfMoves = 0;

    // QSignalMapper is used to map button signal with a slot and also transfer a parameter (in this case information about next position of piece)
    mapper = new QSignalMapper();
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(movePiece(int))); // mapper is the function that will tell what button was pressed and transfer the parameter accordingly

    for (unsigned int index = 0; index < 8; index++)
        for (unsigned int jndex = 0; jndex < 8; jndex++)
        {
            // create positions for each tile
            Position* position = new Position(index, jndex, nullptr);
            this->matrix[index][jndex] = *position;

            // create buttons for each tile linked to position with QSignalMapper
            QPushButton* button = new QPushButton();

            button->setStyleSheet("border: 3px solid gray");
            button->setAutoFillBackground(true);
            button->update();

            button->setFixedWidth(60);
            button->setFixedHeight(60);

            // this sets a map between the button and the parameter that needs to be sent (the indexes)
            mapper->setMapping(button, index*10 + jndex); // index*10 + jndex will send the 2 numbers with the 2 digits because they are both smaller than 10
            connect(button, SIGNAL(clicked()), mapper, SLOT(map())); // connect so it will send a signal to the mapper when clicked

            this->layout->addWidget(button, index, jndex);
        }
    this->widgetTable = new QWidget();
    widgetTable->setLayout(this->layout);
}

void chessBoard::generateTableWith(Piece* piece)
{
    // *** this piece of block is needed so we generate the star based on the type of the piece
    Pawn pawn;
    Bishop bishop;
    const type_info& typePiece = typeid(*piece);
    const type_info& typePawn = typeid(pawn);
    const type_info& typeBishop = typeid(Bishop);
    // ***

    // get a random position of piece
    unsigned int x, y;
    if (typePiece.name() == typePawn.name()) // SPECIAL CASE if it is pawn, do not generate on first line (space for star)
    {
        x = randomNbr() % 8;
        y = randomNbr() % 8;
        while(x == 0) // re-generate until its not on first line
        {
            x = randomNbr() % 8;
        }
    }
    else // regular cases
    {
        x = randomNbr() % 8;
        y = randomNbr() % 8;
    }
    matrix[x][y].setPiece(piece);
    // END position of piece


    // get a random position of star
    unsigned int xStar, yStar;
    if (typePiece.name() == typePawn.name()) // SPECIAL CASE if it is pawn, generate the star so it can be 'eaten'
    {
        xStar = randomNbr() % 8;
        yStar = y;
        while(x <= xStar) // re-generate until its above the piece
        {
            xStar = randomNbr() % 8;
        }
    }
    else if (typePiece.name() == typeBishop.name()) // SPECIAL CASE if bishop generate on (x+y)%2 of piece position
    {
        xStar = randomNbr() % 8;
        yStar = randomNbr() % 8;
        while(((x+y) % 2 != (xStar + yStar) % 2) || (x == xStar && y == yStar)) // on the same diagonals and not on the same position as piece
        {
            xStar = randomNbr() % 8;
            yStar = randomNbr() % 8;
        }
    }
    else // regular case
    {
        xStar = randomNbr() % 8;
        yStar = randomNbr() % 8;

        // re-generate both so they are not the same as piece
        while(y == yStar)
        {
            yStar = randomNbr() % 8;
        }
        while(x == xStar)
        {
            xStar = randomNbr() % 8;
        }
    }
    // END position of star

    matrix[x][y].setPiece(piece);

    matrix[xStar][yStar].setIsStar(true); // property used for table run time formatting

    // set current piece
    this->currentPiece = piece; // remember the piece we are playing with

    // color piece position  --- maybe implement a getStyleSheet for each piece
    this->layout->itemAtPosition(x, y)->widget()->setStyleSheet("background-color: rgb(30,50,70)");
    this->layout->itemAtPosition(x, y)->widget()->update();

    // color star position
    this->layout->itemAtPosition(xStar, yStar)->widget()->setStyleSheet("background-color: rgb(255,255,0)");
    this->layout->itemAtPosition(xStar, yStar)->widget()->update();

    Position pos(x, y, piece);
    colorPossibleMoves(piece->getPossibleMoves(pos));
}

// to use to display message box when reach the star
unsigned int chessBoard::getNumberOfMoves() const
{
    return this->numberOfMoves;
}

QWidget* chessBoard::getTable()
{
    return this->widgetTable;
}

void chessBoard::movePiece(int xy)
{
    // destination indexes ( format xy, where xy was formated as xy = x*10 +y; x,y < 10)
    int x = xy / 10;
    int y = xy % 10;

    Position destinationPos = this->matrix[x][y];


    // is position viable for the piece?
    if (destinationPos.isViablePosition())
    {
        this->numberOfMoves++;

        // first check if star
        if (destinationPos.isStar())
        {
            QMessageBox* winBox = new QMessageBox();
            QString winText = QString("You won after ") + QString::number(float(timer.elapsed())/1000) + QString(" seconds with ") + QString::number(this->numberOfMoves) + QString(" moves!");
            winBox->setText(winText);
            winBox->exec();
            QApplication::exit(200); // exit with code 200 so it will restart (see main.cpp)
            return;
        }

        clearTable();

        // color piece position
        this->layout->itemAtPosition(x, y)->widget()->setStyleSheet("background-color: rgb(30,50,70)");
        this->layout->itemAtPosition(x, y)->widget()->update();

        Position pos(x, y, currentPiece);
        colorPossibleMoves(currentPiece->getPossibleMoves(pos));
    }
}

void chessBoard::clearTable()
{
    for (unsigned int index = 0; index < 8; index++)
        for (unsigned int jndex = 0; jndex < 8; jndex++)
        {
            if (!this->matrix[index][jndex].isStar()) // if not a star, reset to default format
            {
                this->matrix[index][jndex] = Position(index, jndex, nullptr);
                QWidget* button = this->layout->itemAtPosition(index, jndex)->widget();
                button->setStyleSheet("border: 3px solid gray");
                button->update();
            }
            else // if star, reset to star format (if block doesn't exist, it will remain green after leaving)
            {
                this->matrix[index][jndex] = Position(index, jndex, nullptr);
                QWidget* button = this->layout->itemAtPosition(index, jndex)->widget();
                button->setStyleSheet("background-color: rgb(255,255,0)");
                button->update();
            }
            this->matrix[index][jndex].setPossible(false);
        }
}

unsigned int chessBoard::randomNbr()
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(25, 63); // define the range
    return  distr(gen); // generate number
}

void chessBoard::colorPossibleMoves(vector<Position> positions)
{
    for(auto it : positions)
    {
        unsigned int x = it.x(), y = it.y();
        if (matrix[x][y].isStar()) // if it is a star format accordingly
        {
            this->layout->itemAtPosition(x, y)->widget()->setStyleSheet("QPushButton:hover{background-color: rgb(255,255,200)}"
                                                                        "QPushButton:!hover{border: 3px solid darkgreen; background-color: rgb(255,255,0)}");
        }
        else // if it is not a star format accordingly
        {
            this->layout->itemAtPosition(x, y)->widget()->setStyleSheet("QPushButton:hover{background-color: rgb(118,237,123)}"
                                                                        "QPushButton:!hover{border: 3px solid darkgreen; background-color: rgb(100,195,100)}");
        }

        this->layout->itemAtPosition(x, y)->widget()->update();
        this->matrix[x][y].setPossible(true); // make the tile a 'possible to move to tile'
    }
}

void chessBoard::startTimer()
{
    this->timer.start();
}
