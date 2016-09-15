#include "DeckCard.h"
#include "Game.h"

extern Game* sequence;

DeckCard::DeckCard(){}

DeckCard::DeckCard(int value, bool rotate): BoardCard(value, rotate, false){
    this->setAcceptDrops(true); // Le damos el atributo al objeto de que permita Drops

    //this->setFlag(QGraphicsItem::ItemIsSelectable); // Agregamos una box rara al redeador del item
    //setFlag(QGraphicsItem::ItemIsMovable); // Permitimos que el elemento reciba señales de drag
    //setFlag(QGraphicsItem::ItemSendsGeometryChanges); // Envía señales para cambiar la posición
}

void DeckCard::defaultPos(){
    setPos(getPosX(),getPosY());
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

void DeckCard::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsItem::mouseMoveEvent(event); // move the item...
}

void DeckCard::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    defaultPos();
}

