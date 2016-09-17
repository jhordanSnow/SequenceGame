#ifndef UNDOSTACK_H
#define UNDOSTACK_H

#include "Play.h"
#include "DeckCard.h"

class UndoStack{
public:
    UndoStack();
    Play *topPlay();
    void push(int playId, int round, DeckCard *drawedCard, DeckCard* playedCard, BoardCard* tableCard);
    Play* pop();

    void toString();
private:
    Play* first;
    Play* last;
    int size;
};

#endif // UNDOSTACK_H
