#ifndef GAME_H
#define GAME_H

#include "CircleListPlayers.h"
#include "ArrayStackDeck.h"
#include "BoardCard.h"
#include "DeckCard.h"
#include "Button.h"
#include "Player.h"
#include "Token.h"
#include "Board.h"

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
    void loadBoard(int posX, int posY); // Cargamos el tablero
    void cleanRound(Player* player); // Limpiamos la mano del jugador
    void showRound(Player* player); // Mostramos la mano
    void reloadBoard();
    bool tokenTaken(int idToken);
    void setSelectedCard(DeckCard *handCard);
    void checkCards(BoardCard* boardCard);
    void checkWinner(BoardCard* boardCard);

    QGraphicsScene *scene; // Escena del juego
private:
    int numberPlayers; // Cantidad de jugadores
    CircleListPlayers* players; // Lista de jugadores
    ArrayStackDeck* deck; // Array del mazo
    ArrayStackDeck* discardCards;
    Board* tableBoard; //Inicializa el tablero de las cartas
    int round;
    QGraphicsTextItem* playerNameLabel; // Nombre del jugador
    Token* playerToken;
    QString playerName;
    int tokenId;
    DeckCard* selectedHandCard;
public slots:
    void mainMenu(); // Inicia el menú inicial del juego
    void startGame(); // Inicio del juego
    void selectPlayer(); // Menú para la selección de personajes
    void createPlayer(int numberPlayers); // Creación de cada uno de los jugadores
    void getPlayer(int playerId, bool error = false); // Pedimos el nombre y el token del jugador
    void addPlayer(int playerId); // Agregamos el nombre del jugador al array
    void changeName(QString name);
    void startRounds(); // Cargamos las rondas
    void changeToken(); // Cambiamos el token de la selección del personaje
    void randomizeBoard();
};

#endif // GAME_H
