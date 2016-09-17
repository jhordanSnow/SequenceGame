#include "Play.h"

Play::Play(){
    playId = 0;
    round = 0;
    drawedCard = NULL;
    playedCard = NULL;
    nextPlay = NULL;
    previousPlay = NULL;
}

Play::Play(int playId, int round, DeckCard* drawedCard, DeckCard* playedCard, BoardCard *tableCard, Play* previousPlay, Play* nextPay){
    this->playId = playId;
    this->round = round;
    this->drawedCard = drawedCard;
    this->playedCard = playedCard;
    this->tableCard = tableCard;
    this->nextPlay = nextPay;
    this->previousPlay = previousPlay;
}

int Play::getPlayId(){
    return playId;
}

void Play::setPlayId(int value){
    playId = value;
}

DeckCard *Play::getDrawedCard(){
    return drawedCard;
}

void Play::setDrawedCard(DeckCard *value){
    drawedCard = value;
}

Play *Play::getNextPlay(){
    return nextPlay;
}

void Play::setNextPlay(Play *value){
    nextPlay = value;
}

Play *Play::getPreviousPlay(){
    return previousPlay;
}

void Play::setPreviousPlay(Play *value){
    previousPlay = value;
}

Play::~Play(){

}

int Play::getRound()
{
    return round;
}

void Play::setRound(int value)
{
    round = value;
}
