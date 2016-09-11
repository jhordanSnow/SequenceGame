#ifndef GAME_H
#define GAME_H

#include "BoardCard.h"
#include "DeckCard.h"
#include "Button.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

class Game: public QGraphicsView{
    Q_OBJECT
public:
    Game();
    void mainMenu(); // Inicia el menú inicial del juego
    //tablero* tableroCartas; //Inicializa el tablero de las cartas
    //jugador* turno; // Dice el turno del que está jugando

    QGraphicsScene *scene; // Escena del juego
public slots:
    void startGame(); // Inicio del juego
    void selectPlayer(); // Menú para la selección de personajes
    void pickCard(); // Para levantar la carta
};

#endif // GAME_H
