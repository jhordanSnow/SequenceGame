#include "UndoStack.h"

#include "qdebug.h"

UndoStack::UndoStack(){
    first = new Play();
    last = first;
    size = 0;
}

Play* UndoStack::topPlay(){
    return last;
}

void UndoStack::push(int playId, int round, DeckCard *drawedCard, DeckCard* playedCard, BoardCard* tableCard, Player* playerTurn, ArrayBoard* winnerTokens, Player *lastOwner){
    Play* newPlay = new Play(playId, round, drawedCard, playedCard, tableCard, playerTurn, lastOwner, winnerTokens,last);
    last->setNextPlay(newPlay);
    last = newPlay;
    size++;
}

Play* UndoStack::pop(){
    if (size > 0){
        Play* deletedPlay = last;

        last = deletedPlay->getPreviousPlay();
        deletedPlay->getPreviousPlay()->removeNextPlay();
        deletedPlay->setPreviousPlay(NULL);
        size--;
        return deletedPlay;
    }
}

void UndoStack::toString()
{
    Play* temp = first;
    for(int i = 0; i < size; i++){
        qDebug() << temp->getRound();
        temp = temp->getNextPlay();
    }
}

int UndoStack::getSize()
{
    return size;
}

void UndoStack::setSize(int value)
{
    size = value;
}
