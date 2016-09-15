#ifndef BOARD_H
#define BOARD_H

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

    void toString();
private:
    int rows;
    int columns;
    BoardCard*** table;
};

#endif // BOARD_H
