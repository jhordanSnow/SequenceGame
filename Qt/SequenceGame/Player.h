#ifndef PLAYER_H
#define PLAYER_H

#include <QString>

#include "ArrayCard.h"
#include "DeckCard.h"
#include "Token.h"

class Player{
public:
    Player(QString name, Token* playerToken); // Constructor
    QString getName(); // Obtenemos el nombre del jugador

    void setName(QString name); // Seteamos el nombre del jugador

    ArrayCard *getHand();
    void drawCard(DeckCard* card);

    Token* getPlayerToken();
    void setPlayerToken(Token *value);

private:
    QString name; // Nombre del jugador
    ArrayCard* hand; // Array con la mano del jugador
    Token* playerToken;
};

#endif // PLAYER_H
