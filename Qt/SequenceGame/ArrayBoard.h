#ifndef ARRAYBOARD_H
#define ARRAYBOARD_H

#include "BoardCard.h"

class ArrayBoard{
public:
    ArrayBoard(int maxSize, int maxCards); // Constructor
    void setMaxCards(int maxCards); // Seteamo el máximo permitido de cartas
    void appendCard(BoardCard* card); // Agregar una carta
    void swapCards(int cardPos1, int cardPos2); // Cambiar cartas de posiciones
    BoardCard* removeCard(BoardCard *card); // Eliminar una carta


    BoardCard* getCard(int cardPos);
    int getCurrentCardSize();


    void toString();

private:
    BoardCard** cards; // Puntero a los punteros de las cartas
    int maxSize; // Máximo tamaño del array
    int currentCardSize; // Tamaño actual del array
    int maxCards; // Máximo permitido de cartas
};

#endif // ARRAYBOARD_H
