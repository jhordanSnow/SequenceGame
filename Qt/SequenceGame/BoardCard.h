#ifndef BOARDCARD_H
#define BOARDCARD_H

#include <QBrush>
#include <QGraphicsPixmapItem>

class BoardCard: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    BoardCard();
    BoardCard(int value);
    void setPosition(int posX, int posY);
    int getValue();
    int getPosX(); // Traer la posición X de la carta
    int getPosY(); // Traer la posición Y de la carta
    void setSize(float largo); // Método para ajustar el tamaño de la carta con respecto al largo
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event); // Método cuando se pasa el mouse por encima de la carta
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event); // Método cuando sale el mouse de la carta

    virtual ~BoardCard(); // Destructor
private:
    int value; // Valor de la carta
    int posX; // Variable para saber la posición en X de la carta dentro de la pantalla
    int posY; // Variable para saber la posición en Y de la carta dentro de la pantalla
    int state; // Variable para identificar el estado de la carta
};

#endif // BOARDCARD_H
