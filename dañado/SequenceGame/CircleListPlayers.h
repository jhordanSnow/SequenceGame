#ifndef CIRCLELISTPLAYERS_H
#define CIRCLELISTPLAYERS_H

#include "Player.h"

#include <stdexcept>

class CircleListPlayers{
public:
    CircleListPlayers(int maxSize);
    void addPlayer(Player* player);
    void nextPlayer();
    void goToStart();
    Player* getPlayer();
private:
    Player** players;
    int maxSize;
    int currentSize;
    int currentPlayer;
};

#endif // CIRCLELISTPLAYERS_H
