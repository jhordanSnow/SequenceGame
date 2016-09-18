#include "ArrayBoard.h"

#include <qdebug.h>
#include <stdexcept>

using namespace std;

#include "qdebug.h"

ArrayBoard::ArrayBoard(int maxSize, int maxCards){
    this->maxSize = maxSize;
    this->maxCards = maxCards;
    this->currentCardSize = 0;
    cards = new BoardCard*[maxSize];
}

void ArrayBoard::setMaxCards(int maxCards){
    this->maxCards = maxCards;
}

void ArrayBoard::appendCard(BoardCard *card){
    if (currentCardSize == maxSize){
        throw runtime_error("Array is Full.");
    }
    cards[currentCardSize] = card;
    currentCardSize++;
}

void ArrayBoard::swapCards(int cardPos1, int cardPos2){
    BoardCard* tempCard = cards[cardPos1];
    cards[cardPos1] = cards[cardPos2];
    cards[cardPos2] = tempCard;
}

BoardCard *ArrayBoard::removeCard(BoardCard* card){
    int cardPos;
    for (int i = 0; i < currentCardSize; i++){
        if (card == cards[i]){
           cardPos = i;
           break;
        }
    }

    int lastPos = currentCardSize - 1;
    if (cardPos != lastPos){
        swapCards(cardPos,lastPos);
    }
    BoardCard* deletedCard = cards[lastPos];
    currentCardSize--;
    return deletedCard;
}

BoardCard* ArrayBoard::getCard(int cardPos){
    return cards[cardPos];
}

int ArrayBoard::getCurrentCardSize(){
    return currentCardSize;
}

void ArrayBoard::toString()
{
    for (int i = 0; i < currentCardSize; i++){
        qDebug() << cards[i]->getValue();
    }
}
