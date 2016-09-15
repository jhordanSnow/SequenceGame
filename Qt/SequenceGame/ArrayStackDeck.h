#ifndef ARRAYSTACKDECK_H
#define ARRAYSTACKDECK_H

#include "DeckCard.h"

class ArrayStackDeck{
public:
    ArrayStackDeck(int maxSize, int maxCards); // Constructor
    void pushCard(DeckCard* card); // Push de la carta en el top del array
    void fillDeck(); // Llenamos el array con las cartas
    void swapCards(int cardId1, int cardId2); // Cambiar cartas de posiciones
    void shuffleDeck(); // Mezclamos el mazo para que sea aleatorio
    DeckCard* topCard(); // Vemos la carta que está en el top del Array
    DeckCard* popCard(); // Sacamos la carta del top del array y la eliminamos de este


    void toString();
    int getCurrentSize();

private:
    DeckCard** cards; // Puntero a los punteros de la carta
    int maxSize; // Máximo tamaño del array
    int currentSize; // Tamaño actual del array
    int maxCards; // Máximo permitido de cartas
};

#endif // ARRAYSTACKDECK_H
