#ifndef ARRAYSTACKDECK_H
#define ARRAYSTACKDECK_H

#include "DeckCard.h"

class ArrayStackDeck{
public:
    ArrayStackDeck(int maxSize, int maxCards);
    void pushCard(DeckCard* card);
    void fillDeck();
    void swapCards(int cardId1, int cardId2);
    void shuffleDeck();
    DeckCard* topCard();
    DeckCard* popCard();
    bool checkDeck();


    void toString();
private:
    DeckCard** cards;
    int maxSize;
    int currentSize;
    int maxCards;
};

#endif // ARRAYSTACKDECK_H
