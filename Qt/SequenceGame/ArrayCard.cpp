#include "ArrayCard.h"

#include <qdebug.h>
#include <stdexcept>

using namespace std;

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
    DeckCard* deletedCard = cards[lastPos];
    currentCardSize--;
    return deletedCard;
}

DeckCard* ArrayCard::getCard(int cardPos){
    return cards[cardPos];
}

int ArrayCard::getCurrentCardSize(){
    return currentCardSize;
}
