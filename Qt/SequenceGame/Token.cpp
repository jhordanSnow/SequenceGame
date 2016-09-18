#include "Token.h"

const QString PATH_TOKEN = ":/Tokens/Tokens/"; // Ruta de las cartas
const QString EXT_TOKEN = ".png";

Token::Token(int tokenId){
    this->previousRound = false;
    this->tokenId = tokenId;
    QPixmap urlImage = PATH_TOKEN + "dog_" + QString::number(tokenId) + EXT_TOKEN;
    setPixmap(urlImage);
}

void Token::changeToken(int newId){
    this->tokenId = newId;
    QPixmap urlImage = PATH_TOKEN + "dog_" + QString::number(newId) + EXT_TOKEN;
    setPixmap(urlImage);
}

void Token::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit clicked();
}

void Token::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    QPixmap urlImage = PATH_TOKEN + "dog_" + QString::number(tokenId) + "_hover" + EXT_TOKEN;
    setPixmap(urlImage);
}

void Token::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    QPixmap urlImage = PATH_TOKEN + "dog_" + QString::number(tokenId) + "_hover" + EXT_TOKEN;
    setPixmap(urlImage);
}

bool Token::getPreviousRound()
{
    return previousRound;
}

void Token::setPreviousRound(bool value)
{
    previousRound = value;
}

void Token::setTokenId(int tokenId){
    this->tokenId = tokenId;
}

int Token::getTokenId(){
    return tokenId;
}
