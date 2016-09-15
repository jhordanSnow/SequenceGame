#ifndef ARRAYCARD_H
#define ARRAYCARD_H

#include "DeckCard.h"

class ArrayCard{
public:
    ArrayCard(int maxSize, int maxCards); // Constructor
    void setMaxCards(int maxCards); // Seteamo el máximo permitido de cartas
    void appendCard(DeckCard* card); // Agregar una carta
    void swapCards(int cardPos1, int cardPos2); // Cambiar cartas de posiciones
    DeckCard* removeCard(int cardPos); // Eliminar una carta


    DeckCard* getCard(int cardPos);
    int getCurrentCardSize();

private:
    DeckCard** cards; // Puntero a los punteros de las cartas
    int maxSize; // Máximo tamaño del array
    int currentCardSize; // Tamaño actual del array
    int maxCards; // Máximo permitido de cartas
};

#endif // ARRAYCARD_H
