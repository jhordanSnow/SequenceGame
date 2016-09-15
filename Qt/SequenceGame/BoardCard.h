#ifndef BOARDCARD_H
#define BOARDCARD_H

#include <QBrush>
#include <QGraphicsPixmapItem>

class BoardCard: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    BoardCard();
    BoardCard(int value, bool rotate = true, bool board = true); // Constructor
    void setPosition(int posX, int posY); // Seteamos la posición de la carta
    int getValue(); // Obtenemos el valor de la carta
    int getPosX(); // Traer la posición X de la carta
    int getPosY(); // Traer la posición Y de la carta
    void setSize(float largo); // Método para ajustar el tamaño de la carta con respecto al largo
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event); // Método cuando se pasa el mouse por encima de la carta
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event); // Método cuando sale el mouse de la carta
    bool getScale(); // Obtenemos el parametro de si permitimos escalarlo o no
    void setScale(bool allowScale); // Seteamos la variable scale

    virtual ~BoardCard(); // Destructor
private:
    int value; // Valor de la carta
    int posX; // Variable para saber la posición en X de la carta dentro de la pantalla
    int posY; // Variable para saber la posición en Y de la carta dentro de la pantalla
    int state; // Variable para identificar el estado de la carta
    bool allowScale = true; // Variable para verificar si la carta se puede escalar o no
    bool board;
};

#endif // BOARDCARD_H
