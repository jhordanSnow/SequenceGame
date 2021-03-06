#include "CircleListPlayers.h"

using namespace std;

#include <QDebug>

CircleListPlayers::CircleListPlayers(int maxSize){
    this->maxSize = maxSize;
    this->currentSize = 0;
    this->currentPlayer = 0;
    players = new Player*[maxSize];
}

void CircleListPlayers::addPlayer(Player *player){
    if (currentSize > maxSize){
        throw runtime_error("Can't add more plyers.");
    }
    players[currentSize] = player;
    currentSize++;
}

void CircleListPlayers::nextPlayer(){
    currentPlayer++;
    if (currentPlayer == currentSize){
        currentPlayer = 0;
    }

}

void CircleListPlayers::goToStart(){
    this->currentPlayer = 0;
}

Player *CircleListPlayers::getPlayerById(int playerId){
    if (playerId < 0 || playerId > currentSize){
        throw runtime_error("Player ID not found.");
    }
    return players[playerId];
}

void CircleListPlayers::setPlayer(Player* player){
    for (int i = 0; i<currentSize;i++){
        if (players[i] == player){
            currentPlayer = i;
        }
    }
}


Player *CircleListPlayers::getPlayer(){
    if (currentPlayer < 0 || currentPlayer > currentSize){
        throw runtime_error("Player ID not found.");
    }
    return players[currentPlayer];
}

int CircleListPlayers::getCurrentSize(){
    return currentSize;
}

void CircleListPlayers::setCurrentSize(int currentSize){
    this->currentSize = currentSize;
}
