#ifndef CIRCLELISTPLAYERS_H
#define CIRCLELISTPLAYERS_H

#include "Player.h"

#include <stdexcept>

class CircleListPlayers{
public:
    CircleListPlayers(int maxSize); // Constructor
    void addPlayer(Player* player); // Agregamos el jugador a la lista
    void nextPlayer(); // Obtenemos el jugador siguiente
    void goToStart(); // Volvemos al inicio del array
    Player* getPlayer(); // Obtenemos al jugador
    int getCurrentSize();
    void setCurrentSize(int currentSize);
    Player *getPlayerById(int playerId);
private:
    Player** players; // Puntero a jugadores
    int maxSize; // Máximo tamaño del array
    int currentSize; // Tamaño actual del array
    int currentPlayer; // Posición actual del jugador
};

#endif // CIRCLELISTPLAYERS_H
