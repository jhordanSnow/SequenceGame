#include "BoardCard.h"
#include "Game.h"

#define DEFAULT_SIZE 80
#define DEFAULT_ZOOM 120

using namespace std;

const string PATH_CARDS = ":/Cards/Cards/"; // Ruta de las cartas
const string EXT_CARDS = ".png";

extern Game* sequence; // Llamamos a la variable global que controla al juego

BoardCard::BoardCard(){}

BoardCard::BoardCard(int value, QString suit, int posX, int posY){
    /*
    ** Setea la ruta de la imagen deacuerdo al valor y el tipo de esta
    ** y se la agraga al objeto
    */
    QPixmap urlCard = QString::fromStdString(PATH_CARDS + to_string(value) + "_" + suit.toStdString() + EXT_CARDS);
    setPixmap(urlCard);

    /*
    ** Rotamos la imagen para que sea horizontal
    */
    setTransformOriginPoint(DEFAULT_SIZE/4,DEFAULT_SIZE/2);
    setRotation(90);
    /*
    ** Seteamos los valores iniciales de la carta y la posición dentro del view
    */
    this->value = value;
    this->suit = suit;
    this->posX = posX;
    this->posY = posY;

    setPos(posX, posY); // Ubicamos el objeto en las pocisiones dadas
    setAcceptHoverEvents(true); // Hacemos que el objeto permita eventos de mouseHover
    setFlag(QGraphicsItem::ItemIsFocusable); // Permitimos que el objeto tenga foco dentro de la escena

    setSize(DEFAULT_SIZE);
}

int BoardCard::getPosX(){
    return posX;
}

int BoardCard::getPosY(){
    return posY;
}

void BoardCard::setSize(float largo){
    setPixmap(this->pixmap().scaledToHeight(largo));
}

void BoardCard::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    setSize(DEFAULT_ZOOM);
}


void BoardCard::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    setSize(DEFAULT_SIZE);
}

BoardCard::~BoardCard(){

}
