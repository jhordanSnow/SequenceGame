#include "DeckCard.h"

DeckCard::DeckCard(){}

DeckCard::DeckCard(int value, QString suit, int posX, int posY): BoardCard(value, suit, posX, posY){
    this->setAcceptDrops(true); // Le damos el atributo al objeto de que permita Drops

    this->setFlag(QGraphicsItem::ItemIsSelectable); // Agregamos una box rara al redeador del item
    setFlag(QGraphicsItem::ItemIsMovable); // Permitimos que el elemento reciba señales de drag
    setFlag(QGraphicsItem::ItemSendsGeometryChanges); // Envía señales para cambiar la posición
}

void DeckCard::defaultPos(){
    setPos(getPosX(),getPosY());
}

void DeckCard::mousePressEvent(QGraphicsSceneMouseEvent *event){
    qInfo("click event");
}

void DeckCard::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsItem::mouseMoveEvent(event); // move the item...
}

void DeckCard::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    defaultPos();
}

