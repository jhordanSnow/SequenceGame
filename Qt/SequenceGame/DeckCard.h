#ifndef DECKCARD_H
#define DECKCARD_H

#include "BoardCard.h"

class DeckCard : public BoardCard{
public:
    DeckCard();
    DeckCard(int value, QString suit, int posX, int posY);
    void defaultPos(); // Retorna a la posición original
    void mousePressEvent(QGraphicsSceneMouseEvent *event); //  Método para tomar el evento de presionar
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event); // Método para capturar el movimiento del mouse
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event); // Método para capturar cuando se suelta la carta
private:
};

#endif // DECKCARD_H
