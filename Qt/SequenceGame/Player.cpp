#include "Player.h"

Player::Player(QString name, Token *playerToken){
    this->name = name;
    this->playerToken = playerToken;
    hand = new ArrayCard(10,7);
}

QString Player::getName(){
    return name;
}

void Player::setName(QString name){
    this->name = name;
}

ArrayCard *Player::getHand(){
    return hand;
}

void Player::drawCard(DeckCard *card){
    hand->appendCard(card);
}

Token* Player::getPlayerToken(){
    return playerToken;
}

void Player::setPlayerToken(Token* value){
    playerToken = value;
}
