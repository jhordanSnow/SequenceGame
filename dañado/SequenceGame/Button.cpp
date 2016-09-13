#include "Button.h"

using namespace std;

const QString PATH_BUTTON = ":/Buttons/Buttons/"; // Ruta de las cartas
const QString EXT_BUTTON = ".png"; // Extensión de los botones

Button::Button(QString buttonName){
    this->buttonName = buttonName;
    QPixmap urlImage = PATH_BUTTON + buttonName + EXT_BUTTON;
    setPixmap(urlImage); // Url del botón
    setAcceptHoverEvents(true); // Permitimos que se puedan hacer eventos del tipo hover
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    QPixmap urlImage = PATH_BUTTON + buttonName + QString("_hover") + EXT_BUTTON;
    //setCursor(Qt::PointingHandCursor); // Cambiamos el estilo del cursor al de una mano
    setPixmap(urlImage); // Url del botón cuando se pone el mouse encima
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    QPixmap urlImage = PATH_BUTTON + buttonName + EXT_BUTTON;
    //setCursor(Qt::ArrowCursor); // Cambiamos el estilo del cursor nuevamente al de una flecha
    setPixmap(urlImage); // Url del botón cuando el mouse sale de la imagen
}

