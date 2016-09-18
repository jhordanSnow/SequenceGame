#include "Play.h"

#include "qdebug.h"

Play::Play(){
    playId = 0;
    round = 0;
    drawedCard = NULL;
    playedCard = NULL;
    nextPlay = NULL;
    previousPlay = NULL;
    playerTurn = NULL;
}

Play::Play(int playId, int round, DeckCard* drawedCard, DeckCard* playedCard, BoardCard *tableCard, Player *playerTurn, Player *lastOwner, ArrayBoard* winnerTokens, Play* previousPlay){

    this->playId = playId;
    this->round = round;
    this->drawedCard = drawedCard;
    this->playedCard = playedCard;
    this->tableCard = tableCard;
    this->playerTurn = playerTurn;
    this->lastOwner = lastOwner;
    this->previousPlay = previousPlay;
    this->winnerTokens = winnerTokens;
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


void Play::removeNextPlay(){
    nextPlay = new Play();

}

Player *Play::getLastOwner()
{
    return lastOwner;
}

void Play::setLastOwner(Player *value)
{
    lastOwner = value;
}

ArrayBoard *Play::getWinnerTokens()
{
    return winnerTokens;
}

void Play::setWinnerTokens(ArrayBoard *value)
{
    winnerTokens = value;
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

BoardCard *Play::getTableCard()
{
    return tableCard;
}

void Play::setTableCard(BoardCard *value)
{
    tableCard = value;
}

DeckCard *Play::getPlayedCard()
{
    return playedCard;
}

void Play::setPlayedCard(DeckCard *value)
{
    playedCard = value;
}

Player *Play::getPlayerTurn()
{
    return playerTurn;
}

void Play::setPlayerTurn(Player *value)
{
    playerTurn = value;
}
