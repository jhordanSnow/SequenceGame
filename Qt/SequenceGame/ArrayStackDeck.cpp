#include "ArrayStackDeck.h"
#include <stdexcept>

#include <stdlib.h>
#include <ctime>

#include <qdebug.h>

using namespace std;

ArrayStackDeck::ArrayStackDeck(int maxSize, int maxCards){
    this->maxSize = maxSize;
    this->maxCards = maxCards;
    this->currentSize = 0;
    cards = new DeckCard*[maxSize];
}

void ArrayStackDeck::pushCard(DeckCard *card){
    if (currentSize == maxSize){
        throw runtime_error("Full Deck");
    }
    cards[currentSize] = card;
    currentSize++;
}

void ArrayStackDeck::fillDeck(){
    for (int i = 0; i < maxSize; i++){
        int indiceCard = (i % maxCards) + 1;
        pushCard(new DeckCard(indiceCard));
    }
}

void ArrayStackDeck::swapCards(int cardId1, int cardId2){
    DeckCard* tempCard = cards[cardId1];
    cards[cardId1] = cards[cardId2];
    cards[cardId2] = tempCard;
}

void ArrayStackDeck::shuffleDeck(){
    srand((int)time(0));
    for (int i = 0; i < currentSize; i++){
        swapCards(i,rand()%currentSize);
    }
}

DeckCard *ArrayStackDeck::topCard(){
    return cards[currentSize - 1];
}

DeckCard *ArrayStackDeck::popCard(){
    DeckCard* deletedCard = cards[currentSize - 1];
    currentSize--;
    return deletedCard;
}

void ArrayStackDeck::toString(){
    for (int i = 0; i < currentSize; i++){
        qDebug() << cards[i]->getValue();
    }
}

int ArrayStackDeck::getCurrentSize(){
    return currentSize;
}
