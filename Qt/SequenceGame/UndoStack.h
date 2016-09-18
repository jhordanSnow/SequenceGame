#ifndef UNDOSTACK_H
#define UNDOSTACK_H

#include "Play.h"
#include "Player.h"
#include "DeckCard.h"
#include "ArrayBoard.h"

class UndoStack{
public:
    UndoStack();
    Play *topPlay();
    void push(int playId, int round, DeckCard *drawedCard, DeckCard* playedCard, BoardCard* tableCard, Player* playerTurn, ArrayBoard *winnerTokens = NULL,Player* lastOwner = NULL);
    Play* pop();

    void toString();
    int getSize();
    void setSize(int value);

private:
    Play* first;
    Play* last;
    int size;
};

#endif // UNDOSTACK_H
