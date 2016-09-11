#ifndef BUTTON_H
#define BUTTON_H

#include <QBrush>
#include <QGraphicsPixmapItem>

class Button: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Button(QString buttonName); // Constructor
    void mousePressEvent(QGraphicsSceneMouseEvent* event); // Evento cuando se presiona el botón
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event); // Evento cuando se hace Hover
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event); // Evento cuando se finaliza el hover
signals:
    void clicked();
private:
    QString buttonName;
};

#endif // BUTTON_H
