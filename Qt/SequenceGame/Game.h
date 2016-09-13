#ifndef GAME_H
#define GAME_H

#include "BoardCard.h"
#include "DeckCard.h"
#include "Button.h"
#include "Player.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>

#include <QSignalMapper>

class Game: public QGraphicsView{
    Q_OBJECT
public:
    Game();
    //tablero* tableroCartas; //Inicializa el tablero de las cartas
    //jugador* turno; // Dice el turno del que está jugando

    QGraphicsScene *scene; // Escena del juego
public slots:
    void mainMenu(); // Inicia el menú inicial del juego
    void startGame(); // Inicio del juego
    void selectPlayer(); // Menú para la selección de personajes
    void createPlayer(); // Creación de cada uno de los jugadores
};

#endif // GAME_H
