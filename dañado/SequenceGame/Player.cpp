#include "Player.h"

Player::Player(QString name, QString urlToken){
    this->name = name;
    this->urlToken = urlToken;
}

QString Player::getName(){
    return name;
}

QString Player::getToken(){
    return urlToken;
}

void Player::setName(QString name){
    this->name = name;
}

void Player::setToken(QString urlToken){
    this->urlToken = urlToken;
}
