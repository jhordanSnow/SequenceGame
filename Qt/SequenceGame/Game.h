#ifndef GAME_H
#define GAME_H

#include "CircleListPlayers.h"
#include "ArrayStackDeck.h"
#include "UndoStack.h"
#include "ArrayBoard.h"
#include "BoardCard.h"
#include "DeckCard.h"
#include "Button.h"
#include "Player.h"
#include "Token.h"
#include "Board.h"

#include <QEvent>
#include <QMouseEvent>
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
    void checkCards(BoardCard* boardCard, bool isRedo = false);
    void checkWinner(BoardCard* boardCard);
    void changeDiscardImage(BoardCard* boardCard);
    int recursiveSearch(int posCardX, int posCardY, int moveX, int moveY, int cRows, int cCols, BoardCard* boardCard, int tokens);
    QGraphicsScene *scene; // Escena del juego
    void mouseMoveEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);

    void resetGame();
    void winnerMenu();

    void winnerOptions();
    void fillPlayersHand(int maxHandCards);
    void discardHands();
private:
    int numberPlayers; // Cantidad de jugadores
    CircleListPlayers* players; // Lista de jugadores
    ArrayStackDeck* deck; // Array del mazo
    ArrayStackDeck* discardCards;
    Board* tableBoard; //Inicializa el tablero de las cartas
    int round;
    QGraphicsTextItem* playerNameLabel; // Nombre del jugador
    QGraphicsTextItem* roundLabel; // Nombre del jugador
    Token* playerToken;
    QString playerName;
    int tokenId;
    DeckCard* selectedHandCard;
    UndoStack* undoPile;
    UndoStack* redoPile;
    BoardCard* discardImage;

    Player* winnerPlayer;
    ArrayBoard* winnerTokens;
    ArrayBoard* oldWinnerTokens;

    bool usedToken;

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
    void undoFunction();
    void redoFunction();
};

#endif // GAME_H
