#include "ArrayCard.h"

#include <qdebug.h>
#include <stdexcept>

using namespace std;

#include "qdebug.h"

ArrayCard::ArrayCard(int maxSize, int maxCards){
    this->maxSize = maxSize;
    this->maxCards = maxCards;
    this->currentCardSize = 0;
    cards = new DeckCard*[maxSize];
}

void ArrayCard::setMaxCards(int maxCards){
    this->maxCards = maxCards;
}

void ArrayCard::appendCard(DeckCard *card){
    if (currentCardSize == maxSize){
        throw runtime_error("Array is Full.");
    }
    cards[currentCardSize] = card;
    currentCardSize++;
}

DeckCard* ArrayCard::popCard(){
    DeckCard* deletedCard = cards[currentCardSize - 1];
    currentCardSize--;
    return deletedCard;
}

void ArrayCard::swapCards(int cardPos1, int cardPos2){
    DeckCard* tempCard = cards[cardPos1];
    cards[cardPos1] = cards[cardPos2];
    cards[cardPos2] = tempCard;
}

DeckCard *ArrayCard::removeCard(DeckCard* card){
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
    return popCard();
}

DeckCard* ArrayCard::getCard(int cardPos){
    return cards[cardPos];
}

int ArrayCard::getCurrentCardSize(){
    return currentCardSize;
}

void ArrayCard::toString()
{
    for (int i = 0; i < currentCardSize; i++){
        qDebug() << cards[i]->getValue();
    }
}
