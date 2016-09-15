#include "Game.h"
#include <QDebug>

#define GAME_FONT_SIZE 30
const QFont gameFont("SansSerif",GAME_FONT_SIZE);

#define WINNER_ROW 5

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 600
#define MAX_PLAYERS 4
#define MAX_DECK_CARDS 52
#define MAX_DECKS 2
#define BOARD_ROWS 10
#define BOARD_COLUMNS 10
#define BOARD_CARD_WIDTH 42
#define BOARD_CARD_HEIGHT 60
#define DECK_CARD_WIDTH 70
#define MARGIN_CARDS 5
#define BACK_POSX 5
#define BACK_POSY 538
#define INITIAL_BOARD_POSX 450
#define INITIAL_BOARD_POSY 10

#define ID_J_1 49
#define ID_J_2 51

#define ID_JOKER_1 50
#define ID_JOKER_2 52

#define maxToken 4

Game::Game(){
    tokenId = 1;
    /*
    ** Inicializamos la pantalla
    */
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Eliminamos la barra horizontal
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Eliminamos la barra vertical
    setFixedSize(WINDOW_WIDTH,WINDOW_HEIGHT); // Le damos un tamaño fijo
    /*
    ** Inicializamos la escena
    */
    this->scene = new QGraphicsScene();
    scene->setSceneRect(0,0,WINDOW_WIDTH,WINDOW_HEIGHT); // Tamaño de la escena
    setScene(this->scene); // Añadimos la escena

    /*
    ** Inicializamos la lista de los jugadores
    */
    this->players = new CircleListPlayers(MAX_PLAYERS);
    /*
    ** Inicializamos el mazo y lo llenamos con cartas ordenadas
    ** Inicializamos el tablero y lo llenamos
    */
    deck = new ArrayStackDeck(MAX_DECK_CARDS * MAX_DECKS,MAX_DECK_CARDS);
    tableBoard = new Board(BOARD_ROWS,BOARD_COLUMNS);
    deck->fillDeck();
    tableBoard->fillBoard();

    discardCards = new ArrayStackDeck(MAX_DECK_CARDS * MAX_DECKS,MAX_DECK_CARDS);
}

void Game::loadBoard(int posX, int posY){
    for (int i = 0 ; i < tableBoard->getRows(); i++){
        for (int j = 0; j < tableBoard->getColumns(); j++){
            BoardCard* cardAux = tableBoard->getCard(i,j);
            int positionCardX = posX + ((BOARD_CARD_HEIGHT + MARGIN_CARDS) * i);
            int positionCardY = posY + ((BOARD_CARD_WIDTH + MARGIN_CARDS) * j);
            cardAux->setPos(positionCardX, positionCardY);
            scene->addItem(cardAux);
        }
    }
}

void Game::mainMenu(){
    scene->clear();
    setBackgroundBrush(QBrush(QImage(":/Images/Images/main.jpg"))); // Imagen de fondo del menú principal

    /*
    ** Creamos el botón de inicio
    */
    Button* startButton = new Button(QString("start"));
    // Posicionamos el botón en el centro de la pantalla
    startButton->setPosition(WINDOW_WIDTH/2 - startButton->boundingRect().width()/2, WINDOW_HEIGHT/2 - startButton->boundingRect().height()/5);
    // Conectamos el botón con la pantalla de selección de jugadores
    connect(startButton, SIGNAL(clicked()), this, SLOT(selectPlayer()));
    scene->addItem(startButton);

    /*
    ** Creamos el botón de salir (pendiente)
    */
    Button* salir = new Button(QString("Salir"));
    // Posicionamos el botón en el centro de la pantalla
    int sxPos = this->width()/2 - salir->boundingRect().width()/2;
    int syPos = 350;
    salir->setPos(sxPos,syPos);
    // Conectamos el botón con salir de la aplicación
    connect(salir, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(salir);
}

void Game::startGame(){
    scene->clear(); // Resetamos la escena
    setBackgroundBrush(QBrush(QImage(":/Images/Images/background.jpg"))); // Imagen de fondoe
    // Posicionamos el el tablero

    loadBoard(INITIAL_BOARD_POSX,INITIAL_BOARD_POSY);

    deck->shuffleDeck(); // Revolvemos el mazo
    /*
    ** Creamos la imagen del mazo
    */
    BoardCard* deckImage = new BoardCard(-1,false);
    deckImage->setPosition(20, 350);
    deckImage->setScale(false);
    scene->addItem(deckImage);

    Button* randomizeBoard = new Button("back");
    randomizeBoard->setPos(40, 420);
    scene->addItem(randomizeBoard);
    connect (randomizeBoard, SIGNAL(clicked()), this, SLOT(randomizeBoard()));

    /*
    ** Cargamos las manos de cada jugador
    */
    int maxHandCards = (this->numberPlayers == 4) ? 6 : 7;
    players->goToStart();

    for (int i = 0; i < players->getCurrentSize(); i++){
        Player* currentPlayer = players->getPlayer();
        for (int j = 0; j < maxHandCards; j++){
            currentPlayer->drawCard(deck->popCard());
        }
        players->nextPlayer();
    }

    round = 0;
    startRounds();

    /*for (int i = 0; i < players->getCurrentSize(); i++){
        Player* currentPlayer = players->getPlayer();
        qDebug() << currentPlayer->getName();
        qDebug() << "------------------------------";
        currentPlayer->getHand()->toString();
        qDebug() << deck->getCurrentSize();
        players->nextPlayer();
    }*/

}

void Game::selectPlayer(){
    scene->clear(); // Resetamos la escena
    setBackgroundBrush(QBrush(QImage(":/Images/Images/select_player.jpg"))); // Imagen de fondo

    /*
    ** Botón de volver al inicio del juego
    */
    Button* back = new Button(QString("back"));
    back->setPos(BACK_POSX,BACK_POSY);
    connect(back, SIGNAL(clicked()), this, SLOT(mainMenu()));
    scene->addItem(back);

    /*
    ** Creamos el botón para la selección de 2 jugadores
    */
    Button* twoPlayers = new Button(QString("2_players"));
    twoPlayers->setPos(WINDOW_WIDTH/2 - twoPlayers->pixmap().width()/5, twoPlayers->pixmap().height()/4);
    scene->addItem(twoPlayers);

    /*
    ** Creamos el botón para la selección de 3 jugadores
    */
    Button* threePlayers = new Button(QString("3_players"));
    threePlayers->setPos(WINDOW_WIDTH/4,WINDOW_HEIGHT/2 - twoPlayers->pixmap().height()/2.5);
    scene->addItem(threePlayers);

    /*
    ** Creamos el botón para la selección de 4 jugadores
    */
    Button* fourPlayers = new Button(QString("4_players"));
    fourPlayers->setPos(WINDOW_WIDTH/2 - twoPlayers->pixmap().width()/5,WINDOW_HEIGHT/2 - twoPlayers->pixmap().height()/4);
    scene->addItem(fourPlayers);

    /*
    ** Mapeamos la señal para que cada botón mande un parametro
    ** de acuerdo a la cantidad de jugadores que se seleccionen
    */
    QSignalMapper* signalMapper = new QSignalMapper (this);
    connect (twoPlayers, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect (threePlayers, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect (fourPlayers, SIGNAL(clicked()), signalMapper, SLOT(map()));
    /*
    ** Añadimos el valor de cada uno de los botones
    */
    signalMapper -> setMapping (twoPlayers, 2);
    signalMapper -> setMapping (threePlayers, 3);
    signalMapper -> setMapping (fourPlayers, 4);
    /*
    ** Conectamos los botones a la señal de creación del jugador
    */
    connect (signalMapper, SIGNAL(mapped(int)), this, SLOT(createPlayer(int)));
}

void Game::createPlayer(int numberPlayers){
    /*
    ** Avanzamos a la creación del primero personaje
    */
    this->numberPlayers = numberPlayers;
    getPlayer(0);
}

void Game::getPlayer(int playerId, bool error){
    scene->clear();
    setBackgroundBrush(QBrush(QImage(":/Images/Images/background.jpg"))); // Imagen de fondo

    if (playerId < numberPlayers){
        QGraphicsTextItem* playerLabel = new QGraphicsTextItem(QString("Player ") + QString::number(playerId + 1)); // Creamos el label del jugador
        playerLabel->setFont(gameFont); // Seteamos el estilo del titulo
        playerLabel->setPos(550,310);
        scene->addItem(playerLabel);

        /*
        ** Elección del token del jugador
        */
        playerToken = new Token(tokenId);
        playerToken->setPos(40, 150);
        scene->addItem(playerToken);

        connect (playerToken, SIGNAL(clicked()), this, SLOT(changeToken()));

        QLineEdit* playerInputName = new QLineEdit; // Creamo el objeto en donde se escribe el nombre del jugador
        playerInputName->setFont(gameFont);
        QString placeHolderMsg = (error) ? "Name can't be null" : "Write the name of player " + QString::number(playerId + 1) + ".";
        playerInputName->setPlaceholderText(placeHolderMsg);
        playerInputName->setGeometry(550,420,510,65); // Le damos la posición y el tamaño
        scene->addWidget(playerInputName); // Añadimos el input text a la escena

        connect(playerInputName, SIGNAL(textChanged(QString)), this, SLOT(changeName(QString)));

        QSignalMapper* signalMapper = new QSignalMapper(this);

        /*
        ** Botón del back
        */
        Button* back = new Button(QString("back"));
        back->setPos(5,538);
        int previousPlayer = playerId - 1;


        /*
        ** Si el id del jugador es 0, el botón de atras
        ** va a a ir al menú de seleccion de cantidad de jugadores
        ** de lo contrario va a la configuración del jugador anterior
        */
        if (playerId == 0) {
            connect(back, SIGNAL(clicked()), this, SLOT(selectPlayer()));
        }else{
            connect (back, SIGNAL(clicked()), signalMapper, SLOT(map()));
            signalMapper -> setMapping (back, previousPlayer);
            connect (signalMapper, SIGNAL(mapped(int)), this, SLOT(getPlayer(int)));

        }

        scene->addItem(back);

        /*
        ** Botón al siguiente jugador, donde guarda la información de este
        */
        Button* next = new Button(QString("next"));
        next->setPos(1050,538);
        scene->addItem(next);
        connect (next, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper -> setMapping (next, playerId);
        connect (signalMapper, SIGNAL(mapped(int)), this, SLOT(addPlayer(int)));
    }
}

void Game::addPlayer(int playerId){
    // Agregamos el jugador a la lista de jugadore
    if (playerName == ""){
        getPlayer(playerId, true);
        return;
    }
    players->addPlayer(new Player(playerName, new Token(tokenId)));
    playerName = "";
    tokenId = (tokenId % maxToken) + 1;
    playerId++;
    /*
    ** Si el jugador siguiente es igual a la cantidad máxima de jugadores
    ** vamos a la ventana inicial del juego, de lo contrario lo llevamos
    ** a la creación del siguiente jugador
    */
    if (playerId == numberPlayers){
        startGame();
    }else{
        getPlayer(playerId);
    }
}

void Game::changeName(QString name){
    playerName = name;
}

void Game::startRounds(){
    if (round > 0){
        cleanRound(players->getPlayer());
        players->nextPlayer();
    }

    Player* currentPlayer = players->getPlayer();
    showRound(currentPlayer);

    Button* next = new Button(QString("next"));
    next->setPos(1050,538);
    connect (next, SIGNAL(clicked()), this, SLOT(startRounds()));

    round++;


    scene->addItem(next);
}

void Game::cleanRound(Player* player){
    scene->removeItem(playerToken);
    scene->removeItem(playerNameLabel);
    ArrayCard* currentHand = player->getHand();
    for (int i = 0; i < currentHand->getCurrentCardSize(); i++){
        scene->removeItem(currentHand->getCard(i));
    }
}

void Game::showRound(Player* player){
    playerToken = player->getPlayerToken();
    playerToken->setPos(40,120);
    scene->addItem(playerToken);
    //qDebug() << tokenTemp->getTokenId();

    playerNameLabel = new QGraphicsTextItem(player->getName()); // Creamos el label del jugador
    playerNameLabel->setFont(gameFont); // Seteamos el estilo del titulo
    playerNameLabel->setPos(30,50);
    scene->addItem(playerNameLabel);

    /*Token* tokenTemp = player->getPlayerToken();
    tokenTemp->setPos(45,80);
    scene->addItem(tokenTemp);*/

    ArrayCard* currentHand = player->getHand();
    int initialPosHand = INITIAL_BOARD_POSX;
    for (int i = 0; i < currentHand->getCurrentCardSize(); i++){
        DeckCard* handCard = currentHand->getCard(i);
        handCard->setPosition(initialPosHand+(i*DECK_CARD_WIDTH), WINDOW_HEIGHT - handCard->pixmap().height()/2);
        scene->addItem(handCard);
    }
}

void Game::changeToken(){
    tokenId = (playerToken->getTokenId() % maxToken) + 1;
    while (tokenTaken(tokenId)){
        tokenId = (tokenId % maxToken) + 1;
    }
    playerToken->changeToken(tokenId);
}

bool Game::tokenTaken(int idToken){
    for (int i = 0; i < players->getCurrentSize(); i++){
        if (players->getPlayerById(i)->getPlayerToken()->getTokenId() == idToken){
            return true;
        }
    }
    return false;
}

void Game::randomizeBoard(){
    tableBoard->randomBoard();
    reloadBoard();
}

void Game::setSelectedCard(DeckCard* handCard){
    this->selectedHandCard = handCard;
}

void Game::checkCards(BoardCard *boardCard){
    int handCardId =  (selectedHandCard == NULL) ? NULL : selectedHandCard->getValue();
    if((boardCard->getValue() == handCardId || handCardId == ID_J_1 || handCardId == ID_J_2)
            && !boardCard->getHasOwner() && boardCard->getValue() > 0){

        discardCards->pushCard(selectedHandCard);
        players->getPlayer()->getHand()->removeCard(selectedHandCard);
        boardCard->setOwner(players->getPlayer());
        boardCard->reloadCard();
        scene->removeItem(selectedHandCard);
        selectedHandCard = NULL;
        players->getPlayer()->drawCard(deck->popCard());

        round++;

        checkWinner(boardCard);
        //startRounds();
    }else if (handCardId == ID_JOKER_1 || handCardId == ID_JOKER_2){

        boardCard->setOwner(NULL);
        boardCard->reloadCard();
        scene->removeItem(selectedHandCard);
        selectedHandCard = NULL;
        players->getPlayer()->drawCard(deck->popCard());

        round++;
        //startRounds();
    }else{
        qDebug() << "Nop nigga";
    }
}

void Game::checkWinner(BoardCard* boardCard){
    int posMatrixX = tableBoard->getMatrizPosX(boardCard);
    int posMatrixY = tableBoard->getMatrizPosY(boardCard);
    int matrixRows = tableBoard->getRows();
    int matrixCols = tableBoard->getColumns();

    int horizontalTokens = 1 + recursiveSearch(posMatrixX, posMatrixY, 1, 0,matrixRows, matrixCols, boardCard, 0) + recursiveSearch(posMatrixX, posMatrixY, -1, 0,matrixRows, matrixCols, boardCard, 0);
    int verticalTokens = 1 + recursiveSearch(posMatrixX, posMatrixY, 0, 1,matrixRows, matrixCols, boardCard, 0) + recursiveSearch(posMatrixX, posMatrixY, 0, -1,matrixRows, matrixCols, boardCard, 0);
    int diagonalDown = 1 + recursiveSearch(posMatrixX, posMatrixY, 1, 1,matrixRows, matrixCols, boardCard, 0) + recursiveSearch(posMatrixX, posMatrixY, -1, -1,matrixRows, matrixCols, boardCard, 0);
    int diagonalUp = 1 + recursiveSearch(posMatrixX, posMatrixY, 1, -1,matrixRows, matrixCols, boardCard, 0) + recursiveSearch(posMatrixX, posMatrixY, -1, 1,matrixRows, matrixCols, boardCard, 0);

    /*qDebug() << "Horizontal = " << horizontalTokens;
    qDebug() << "Vertical = " << verticalTokens;
    qDebug() << "Diagonal creciente = " << diagonalUp;
    qDebug() << "Diagonal decreciente = " << diagonalDown;
    qDebug() << "-------------------------------------------------------------------------";*/

}

int Game::recursiveSearch(int posCardX, int posCardY, int moveX, int moveY, int cRows, int cCols, BoardCard* boardCard, int tokens){
    int newPosX = posCardX + moveX;
    int newPosY = posCardY + moveY;
    if (newPosX < 0 || newPosX > (cRows - 1)){
        return tokens;
    }if (newPosY < 0 || newPosY > (cCols - 1)){
        return tokens;
    }
    BoardCard* nextCard = tableBoard->getCard(newPosX, newPosY);
    if (nextCard->getOwner() == boardCard->getOwner()){
        return recursiveSearch(newPosX,newPosY,moveX,moveY,cRows,cCols,nextCard,tokens + 1);
    }
    if ((newPosX == 0 && newPosY == 0) || (newPosX == 9 && newPosY == 9) ||
        (newPosX == 9 && newPosY == 0) || (newPosX == 0 && newPosY == 9)){
        return tokens + 1;
    }
    return tokens;
}

void Game::reloadBoard(){
    for (int i = 0 ; i < tableBoard->getRows(); i++){
        for (int j = 0; j < tableBoard->getColumns(); j++){
            scene->removeItem(tableBoard->getCard(i,j));
            BoardCard* cardAux = tableBoard->getCard(i,j);
            int positionCardX = INITIAL_BOARD_POSX + ((BOARD_CARD_HEIGHT + MARGIN_CARDS) * i);
            int positionCardY = INITIAL_BOARD_POSY + ((BOARD_CARD_WIDTH + MARGIN_CARDS) * j);
            cardAux->setPos(positionCardX, positionCardY);
            scene->addItem(cardAux);
        }
    }
}
