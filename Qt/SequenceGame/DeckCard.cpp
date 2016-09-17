#include "DeckCard.h"
#include "Game.h"

extern Game* sequence;

DeckCard::DeckCard(){}

DeckCard::DeckCard(int value, bool rotate): BoardCard(value, rotate, false){
    this->setAcceptDrops(true); // Le damos el atributo al objeto de que permita Drops
}

void DeckCard::defaultPos(){
    setPos(getPosX(),getPosY());
}

void DeckCard::defaultSize(){
    setSize(200);
}

void DeckCard::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    setZValue(1);
    setPos(getPosX(), getPosY() - pixmap().height()/4);
}

void DeckCard::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    setZValue(0);
    setPos(getPosX(),getPosY());
}

void DeckCard::mousePressEvent(QGraphicsSceneMouseEvent *event){
    sequence->setSelectedCard(this);
}

