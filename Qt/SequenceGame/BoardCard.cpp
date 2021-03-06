#include "BoardCard.h"
#include "Game.h"

#define DEFAULT_SIZE_TOKEN 45
#define DEFAULT_SIZE 60
#define DEFAULT_ZOOM 150

using namespace std;

const string PATH_CARDS = ":/Cards/Cards/"; // Ruta de las cartas
const string EXT_CARDS = ".png";

const string PATH_TOKEN = ":/Tokens/Tokens/"; // Ruta de las cartas
const string EXT_TOKEN = ".png";

extern Game* sequence; // Llamamos a la variable global que controla al juego

#include <qdebug.h>

BoardCard::BoardCard(){}

BoardCard::BoardCard(int value, bool rotate, bool board){
    hasOwner = false;
    setZValue(0);
    /*
    ** Setea la ruta de la imagen deacuerdo al valor y el tipo de esta
    ** y se la agraga al objeto
    */
    QPixmap urlCard = QString::fromStdString(PATH_CARDS + to_string(value) + EXT_CARDS);
    setPixmap(urlCard);

    /*
    ** Rotamos la imagen para que sea horizontal
    */
    if (rotate){
        setTransformOriginPoint(DEFAULT_SIZE/4,DEFAULT_SIZE/2);
        setRotation(270);
    }
    /*
    ** Seteamos los valores iniciales de la carta
    */
    this->value = value;
    this->board = board;

    setAcceptHoverEvents(true); // Hacemos que el objeto permita eventos de mouseHover
    setFlag(QGraphicsItem::ItemIsFocusable); // Permitimos que el objeto tenga foco dentro de la escena
    if (this->allowScale && value >= 0 && this->board){
        setSize(DEFAULT_SIZE);
    }
}

void BoardCard::setPosition(int posX, int posY){
    this->posX = posX;
    this->posY = posY;
    setPos(posX, posY); // Ubicamos el objeto en las pocisiones dadas
}

int BoardCard::getValue(){
    return value;
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
    if (this->allowScale && value > 0 && this->board){
        setZValue(2);
        setRotation(0);
        QPixmap urlCard = QString::fromStdString(PATH_CARDS + to_string(value) + EXT_CARDS);
        setPixmap(urlCard);

    }
}


void BoardCard::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    if (this->allowScale && value >= 0 && this->board){
        setZValue(0);
        setRotation(270);
        setSize(DEFAULT_SIZE);
    }
}

BoardCard::~BoardCard(){

}

bool BoardCard::getHasOwner(){
    return hasOwner;
}

void BoardCard::setHasOwner(bool value){
    hasOwner = value;
}

Token *BoardCard::getTokenCard()
{
    return tokenCard;
}

void BoardCard::setTokenCard(Token *value)
{
    tokenCard = value;
}

Player *BoardCard::getOwner(){
    return owner;
}

void BoardCard::setOwner(Player* owner){
    if (owner != NULL){
        this->owner = owner;
        hasOwner = true;
    }else{
        this->owner = NULL;
        hasOwner = false;
    }
}

bool BoardCard::getScale(){
    return allowScale;
}

void BoardCard::setScale(bool allowScale){
    this->allowScale = allowScale;
}

void BoardCard::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if (this->board && event->button() == Qt::RightButton){
        setZValue(0);
        setRotation(270);
        setSize(DEFAULT_SIZE);
    }
    if (this->board && event->button() == Qt::LeftButton){
        sequence->checkCards(this);
    }
}

void BoardCard::reloadCard(){
   if (hasOwner){
       tokenCard = new Token(owner->getPlayerToken()->getTokenId());
       tokenCard->setPos(getPosX(),getPosY());
       tokenCard->setPixmap(tokenCard->pixmap().scaledToHeight(DEFAULT_SIZE_TOKEN));
       sequence->scene->addItem(tokenCard);
       tokenCard->setZValue(1);
    }else{
       if (this->board){
           sequence->scene->removeItem(tokenCard);
           tokenCard = NULL;
           if (this->allowRotate){
               setTransformOriginPoint(DEFAULT_SIZE/4,DEFAULT_SIZE/2);
               setRotation(270);
           }
       }

       QPixmap urlCard = QString::fromStdString(PATH_CARDS + to_string(value) + EXT_CARDS);
       setPixmap(urlCard);
       if (this->allowScale && value >= 0 && this->board){
           setSize(DEFAULT_SIZE);
       }
   }
}
