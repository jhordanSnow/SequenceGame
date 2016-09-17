#ifndef DECKCARD_H
#define DECKCARD_H

#include "BoardCard.h"

class DeckCard : public BoardCard{
public:
    DeckCard();
    DeckCard(int value, bool rotate = false); // Constructor
    void defaultPos(); // Retorna a la posición original
    void defaultSize();

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event); // Método cuando se pasa el mouse por encima de la carta
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event); // Método cuando sale el mouse de la carta

    void mousePressEvent(QGraphicsSceneMouseEvent *event); //  Método para tomar el evento de presionar
};

#endif // DECKCARD_H
