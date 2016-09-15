#ifndef BUTTON_H
#define BUTTON_H

#include "Game.h"

#include <QBrush>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>

class Button: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Button(QString buttonName); // Constructor
    void mousePressEvent(QGraphicsSceneMouseEvent* event); // Evento cuando se presiona el botón
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event); // Evento cuando se hace Hover
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event); // Evento cuando se finaliza el hover

    void setPosition(int posX, int posY);
signals:
    void clicked();
private:
    QString buttonName;
};

#endif // BUTTON_H
