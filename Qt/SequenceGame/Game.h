#ifndef GAME_H
#define GAME_H

#include "CircleListPlayers.h"
#include "BoardCard.h"
#include "DeckCard.h"
#include "Button.h"
#include "Player.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>

#include <QSignalMapper>
#include <QLineEdit>

class Game: public QGraphicsView{
    Q_OBJECT
public:
    Game();
    void loadDeck(); // Cargamos el mazo
    void loadBoard(bool random = true); // Cargamos el tablero
    //tablero* tableroCartas; //Inicializa el tablero de las cartas
    //jugador* turno; // Dice el turno del que está jugando

    QGraphicsScene *scene; // Escena del juego
private:
    int numberPlayers; // Cantidad de jugadores
    CircleListPlayers* players;
public slots:
    void mainMenu(); // Inicia el menú inicial del juego
    void startGame(); // Inicio del juego
    void selectPlayer(); // Menú para la selección de personajes
    void createPlayer(int numberPlayers); // Creación de cada uno de los jugadores
    void getPlayer(int playerId); // Pedimos el nombre y el token del jugador
    void addPlayer(int playerId); // Agregamos el nombre del jugador al array
};

#endif // GAME_H
