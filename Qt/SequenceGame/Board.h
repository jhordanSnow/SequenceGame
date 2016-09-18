#ifndef BOARD_H
#define BOARD_H

#include "ArrayBoard.h"
#include "BoardCard.h"

class Board{
public:
    Board(int rows, int columns);
    BoardCard* getCard(int row, int column);
    void addCard(int row, int column, BoardCard* card);
    int getRows();
    int getColumns();
    void fillBoard(); // Llenamos el tablero con el patron usado en sequence
    void randomBoard();
    bool isCorner(BoardCard* card);
    int getMatrizPosX(BoardCard* card);
    int getMatrizPosY(BoardCard* card);

    void resetBoard(ArrayBoard* tokenCards = NULL, ArrayBoard *tokenCards2 = NULL);

    void toString();
    bool winnerCard(ArrayBoard *tokenCards, BoardCard *card, ArrayBoard *tokenCards2);
private:
    int rows;
    int columns;
    BoardCard*** table;
};

#endif // BOARD_H
