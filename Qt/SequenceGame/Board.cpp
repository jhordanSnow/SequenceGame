#include "Board.h"

#include <stdexcept>
#include <ctime>

#include <qdebug.h>

using namespace std;
Board::Board(int rows, int columns){
    this->rows = rows;
    this->columns = columns;

    table = new BoardCard**[rows];
    for (int i = 0; i < rows; i++) {
        table[i] = new BoardCard*[columns];
    }

}

BoardCard *Board::getCard(int row, int column){
    if (row < 0 || row >= rows) {
        throw runtime_error("Row not found.");
    }
    if (column < 0 || column >= columns) {
        throw runtime_error("Column not found.");
    }
    return table[row][column];
}

void Board::addCard(int row, int column, BoardCard *card){
    if (row < 0 || row > rows) {
        throw runtime_error("Row not found.");
    }
    if (column < 0 || column > columns) {
        throw runtime_error("Column not found.");
    }
    table[row][column] = card;
}

int Board::getRows(){
    return rows;
}

int Board::getColumns(){
    return columns;
}

void Board::toString(){
    for (int i = 0 ; i < 10; i++){
        for (int j = 0; j<10; j++){
            qDebug() << table[i][j]->getValue() << endl;
        }
    }
}

void Board::randomBoard(){
    srand((int)time(0));
    for (int i = 0 ; i < rows; i++){
        for (int j = 0; j < columns; j++){
            int randomRow = rand()%rows;
            int randomCol = rand()%columns;
            if (!(isCorner(table[i][j])) && !(isCorner(table[randomRow][randomCol]))){
                BoardCard* tmpCard = table[i][j];
                table[i][j] = table[randomRow][randomCol];
                table[randomRow][randomCol] = tmpCard;
            }
        }
    }
}

bool Board::isCorner(BoardCard *card){
    return (card->getValue() == 0);
}

void Board::fillBoard(){
    table[0][0] = new BoardCard(0); // Comodin
    table[0][1] = new BoardCard(2); // A diamantes
    table[0][2] = new BoardCard(46); // K diamantes
    table[0][3] = new BoardCard(42); // Q diamantes
    table[0][4] = new BoardCard(38); // 10 diamantes
    table[0][5] = new BoardCard(34); // 9 diamantes
    table[0][6] = new BoardCard(30); // 8 diamantes
    table[0][7] = new BoardCard(26); // 7 diamantes
    table[0][8] = new BoardCard(22); // 6 diamantes
    table[0][9] = new BoardCard(0); // Comodin

    table[1][0] = new BoardCard(4); // A trebol
    table[1][1] = new BoardCard(27); // 7 picas
    table[1][2] = new BoardCard(23); // 6 picas
    table[1][3] = new BoardCard(19); // 5 picas
    table[1][4] = new BoardCard(15); // 4 picas
    table[1][5] = new BoardCard(11); // 3 picas
    table[1][6] = new BoardCard(7); // 2 picas
    table[1][7] = new BoardCard(5); // 2 corazones
    table[1][8] = new BoardCard(9); // 3 corazones
    table[1][9] = new BoardCard(18); // 5 diamantes

    table[2][0] = new BoardCard(48); // k trebol
    table[2][1] = new BoardCard(31); // 8 picas
    table[2][2] = new BoardCard(40); // 10 trebol
    table[2][3] = new BoardCard(44); // Q trebol
    table[2][4] = new BoardCard(48); // K trebol
    table[2][5] = new BoardCard(4); // A trebol
    table[2][6] = new BoardCard(2); // A diamantes
    table[2][7] = new BoardCard(46); // K diamantes
    table[2][8] = new BoardCard(13); // 4 corazones
    table[2][9] = new BoardCard(14); // 4 diamantes

    table[3][0] = new BoardCard(44); // Q trebol
    table[3][1] = new BoardCard(35); // 9 picas
    table[3][2] = new BoardCard(36); // 9 trebol
    table[3][3] = new BoardCard(29); // 8 corazones
    table[3][4] = new BoardCard(33); // 9 corazones
    table[3][5] = new BoardCard(37); // 10 corazones
    table[3][6] = new BoardCard(41); // q corazones
    table[3][7] = new BoardCard(42); // q diamantes
    table[3][8] = new BoardCard(17); // 5 corazones
    table[3][9] = new BoardCard(10); // 3 diamantes

    table[4][0] = new BoardCard(40); // 10 trebol
    table[4][1] = new BoardCard(39); // 10 picas
    table[4][2] = new BoardCard(32); // 8 trebol
    table[4][3] = new BoardCard(25); // 7 corazones
    table[4][4] = new BoardCard(5); // 2 corazones
    table[4][5] = new BoardCard(9); // 3 corazones
    table[4][6] = new BoardCard(45); // k corazones
    table[4][7] = new BoardCard(38); // 10 diamantes
    table[4][8] = new BoardCard(21); // 6 corazones
    table[4][9] = new BoardCard(6); // 2 diamantes

    table[5][0] = new BoardCard(36); // 9 trebol
    table[5][1] = new BoardCard(43); // q picas
    table[5][2] = new BoardCard(28); // 7 trebol
    table[5][3] = new BoardCard(21); // 6 corazones
    table[5][4] = new BoardCard(17); // 5 corazones
    table[5][5] = new BoardCard(13); //4 corazones
    table[5][6] = new BoardCard(1); // a corazones
    table[5][7] = new BoardCard(34); // 9 diamantes
    table[5][8] = new BoardCard(25); // 7 corazones
    table[5][9] = new BoardCard(3); // A trebol

    table[6][0] = new BoardCard(32); // 8 trebol
    table[6][1] = new BoardCard(48); //k picas
    table[6][2] = new BoardCard(24); // 6 trebol
    table[6][3] = new BoardCard(20); // 5 trebol
    table[6][4] = new BoardCard(16); // 4 trebol
    table[6][5] = new BoardCard(12); // 3 trebol
    table[6][6] = new BoardCard(8); // 2 trebol
    table[6][7] = new BoardCard(30); // 8 diamantes
    table[6][8] = new BoardCard(29); // 8 corazones
    table[6][9] = new BoardCard(48); // k picas

    table[7][0] = new BoardCard(28); // 7 trebol
    table[7][1] = new BoardCard(3); // a picas
    table[7][2] = new BoardCard(6); // 2 diamantes
    table[7][3] = new BoardCard(10); // 3 diamantes
    table[7][4] = new BoardCard(14); // 4 diamantes
    table[7][5] = new BoardCard(18); // 5 diamantes
    table[7][6] = new BoardCard(22); // 6 diamantes
    table[7][7] = new BoardCard(26); // 7 diamantes
    table[7][8] = new BoardCard(33); // 9 corazones
    table[7][9] = new BoardCard(35); // q picas

    table[8][0] = new BoardCard(24); // 6 trebol
    table[8][1] = new BoardCard(20); // 5 trebol
    table[8][2] = new BoardCard(16); // 4 trebol
    table[8][3] = new BoardCard(12); // 3 trebol
    table[8][4] = new BoardCard(8); // 2 trebol
    table[8][5] = new BoardCard(1); // a corazones
    table[8][6] = new BoardCard(45); // k corazones
    table[8][7] = new BoardCard(41); // q corazones
    table[8][8] = new BoardCard(37); // 10 corazones
    table[8][9] = new BoardCard(39); // 10 picas

    table[9][0] = new BoardCard(0); // Comodin
    table[9][1] = new BoardCard(7); // 2 picas
    table[9][2] = new BoardCard(11); // 3 picas
    table[9][3] = new BoardCard(15); // 4 picas
    table[9][4] = new BoardCard(19); // 5 picas
    table[9][5] = new BoardCard(23); // 6 picas
    table[9][6] = new BoardCard(27); // 7 picas
    table[9][7] = new BoardCard(31); // 8 picas
    table[9][8] = new BoardCard(35); // 9 picas
    table[9][9] = new BoardCard(0); // Comodin
}
