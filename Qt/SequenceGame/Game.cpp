#include "Game.h"
#include <qdebug.h>

#define GAME_FONT_SIZE 25
const QFont gameFont("SansSerif",GAME_FONT_SIZE);

Button* restartGame;
Button* exitGame;
Button* newGame;

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
#define INITIAL_BOARD_POSX 520
#define INITIAL_BOARD_POSY 10
#define ID_J_1 49
#define ID_J_2 51
#define ID_JOKER_1 50
#define ID_JOKER_2 52

#define maxToken 68

#define MAX_WINS 2

Game::Game(){
    tokenId = 1;
    endGame = false;
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
    this->winnerScene = NULL;
    scene->addItem(winnerScene);
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

    undoPile = new UndoStack();
    redoPile = new UndoStack();

    roundLabel = NULL;

    selectedHandCard = NULL;

    winnerPlayer = NULL;
    oldWinnerTokens = NULL;
    usedToken = false;
    winnerTokens = new ArrayBoard(5,5);
}

void Game::loadBoard(int posX, int posY){
    for (int i = 0 ; i < tableBoard->getRows(); i++){
        for (int j = 0; j < tableBoard->getColumns(); j++){
            BoardCard* cardAux = tableBoard->getCard(i,j);
            int positionCardX = posX + ((BOARD_CARD_HEIGHT + MARGIN_CARDS) * i);
            int positionCardY = posY + ((BOARD_CARD_WIDTH + MARGIN_CARDS) * j);
            cardAux->setPosition(positionCardX, positionCardY);
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
    deckImage->setPosition(250, 350);
    deckImage->setScale(false);
    scene->addItem(deckImage);

    discardImage = new BoardCard(-2,false);
    discardImage->setPosition(20, 350);
    discardImage->setScale(false);
    scene->addItem(discardImage);

    Button* undoButton = new Button("undo");
    undoButton->setPos(242, 530);
    scene->addItem(undoButton);
    undoButton->setZValue(1);
    connect (undoButton, SIGNAL(clicked()), this, SLOT(undoFunction()));

    Button* redoButton = new Button("redo");
    redoButton->setPos(312, 530);
    scene->addItem(redoButton);
    redoButton->setZValue(1);
    connect (redoButton, SIGNAL(clicked()), this, SLOT(redoFunction()));

    /*
    ** Cargamos las manos de cada jugador
    */
    int maxHandCards = (this->numberPlayers == 4) ? 6 : 7;
    fillPlayersHand(maxHandCards);

    players->goToStart();

    round = 0;
    startRounds();
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
            scene->addItem(back);
        }else{
            connect (back, SIGNAL(clicked()), signalMapper, SLOT(map()));
            signalMapper -> setMapping (back, previousPlayer);
            connect (signalMapper, SIGNAL(mapped(int)), this, SLOT(getPlayer(int)));

        }


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
    if (playerId == numberPlayers && endGame){
        resetGame();
    }else if (playerId == numberPlayers){
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
    }else{
        Button* randomizeBoard = new Button("random");
        randomizeBoard->setPos(40, 420);
        scene->addItem(randomizeBoard);
        randomizeBoard->setZValue(0);
        connect (randomizeBoard, SIGNAL(clicked()), this, SLOT(randomizeBoard()));
    }

    Player* currentPlayer = players->getPlayer();
    showRound(currentPlayer);
}

void Game::cleanRound(Player* player){
    scene->removeItem(playerToken);
    scene->removeItem(playerNameLabel);
    scene->removeItem(roundLabel);
    ArrayCard* currentHand = player->getHand();
    for (int i = 0; i < currentHand->getCurrentCardSize(); i++){
        scene->removeItem(currentHand->getCard(i));
    }
}

void Game::showRound(Player* player){
    playerToken = player->getPlayerToken();
    playerToken->setPos(60,150);
    scene->addItem(playerToken);

    roundLabel = new QGraphicsTextItem("Round #" + QString::number(round + 1)); // Creamos el label del jugador
    roundLabel->setFont(gameFont); // Seteamos el estilo del titulo
    roundLabel->setPos(50,20);
    scene->addItem(roundLabel);

    playerNameLabel = new QGraphicsTextItem(player->getName()); // Creamos el label del jugador
    playerNameLabel->setFont(gameFont); // Seteamos el estilo del titulo
    playerNameLabel->setPos(50,60);
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

void Game::checkCards(BoardCard *boardCard, bool isRedo){
    int handCardId =  (selectedHandCard == NULL) ? NULL : selectedHandCard->getValue();
    Player* turnPlayer = players->getPlayer();

    if((boardCard->getValue() == handCardId || handCardId == ID_J_1 || handCardId == ID_J_2)
            && !boardCard->getHasOwner() && boardCard->getValue() > 0){

        discardCards->pushCard(selectedHandCard);
        changeDiscardImage(selectedHandCard);
        turnPlayer->getHand()->removeCard(selectedHandCard);
        boardCard->setOwner(turnPlayer);
        boardCard->reloadCard();

        DeckCard* drawedCard = deck->popCard();
        DeckCard* playedCard = selectedHandCard;

        scene->removeItem(selectedHandCard);
        selectedHandCard = NULL;

        turnPlayer->drawCard(drawedCard);
        winnerTokens = new ArrayBoard(5,5);
        checkWinner(boardCard);
        undoPile->push(1, round, drawedCard, playedCard, boardCard, turnPlayer, winnerTokens);
        if (!isRedo){
            redoPile = new UndoStack();
        }
        round++;
        if (!endGame){
            startRounds();
        }
    }else if (handCardId == ID_JOKER_1 || handCardId == ID_JOKER_2){
        if (boardCard->getHasOwner() && boardCard->getOwner() != players->getPlayer()){
            discardCards->pushCard(selectedHandCard);

            Player* lastOwner = boardCard->getOwner();

            boardCard->setOwner(NULL);
            boardCard->reloadCard();

            DeckCard* playedCard = selectedHandCard;

            changeDiscardImage(selectedHandCard);
            turnPlayer->getHand()->removeCard(selectedHandCard);
            scene->removeItem(selectedHandCard);
            selectedHandCard = NULL;

            DeckCard* drawedCard = deck->popCard();

            players->getPlayer()->drawCard(drawedCard);

            undoPile->push(2, round, drawedCard, playedCard, boardCard, turnPlayer, winnerTokens,lastOwner);

            round++;

            if (!isRedo){
                redoPile = new UndoStack();
            }
            startRounds();
        }
    }else{
        qDebug() << "Nop nigga";
    }
}

void Game::checkWinner(BoardCard* boardCard){
    int posMatrixX = tableBoard->getMatrizPosX(boardCard);
    int posMatrixY = tableBoard->getMatrizPosY(boardCard);
    int matrixRows = tableBoard->getRows();
    int matrixCols = tableBoard->getColumns();

    winnerTokens = new ArrayBoard(5,5);
    usedToken = false;
    winnerTokens->appendCard(boardCard);

    int horizontalTokens = 1 + recursiveSearch(posMatrixX, posMatrixY, 1, 0,matrixRows, matrixCols, boardCard, 0) + recursiveSearch(posMatrixX, posMatrixY, -1, 0,matrixRows, matrixCols, boardCard, 0);
    if (horizontalTokens >= WINNER_ROW){

        winnerPlayer = players->getPlayer();
        endGame = true;
        winnerOptions();

    }else{

        winnerTokens = new ArrayBoard(5,5);
        usedToken = false;
        winnerTokens->appendCard(boardCard);

        int verticalTokens = 1 + recursiveSearch(posMatrixX, posMatrixY, 0, 1,matrixRows, matrixCols, boardCard, 0) + recursiveSearch(posMatrixX, posMatrixY, 0, -1,matrixRows, matrixCols, boardCard, 0);
        if (verticalTokens >= WINNER_ROW){

            winnerPlayer = players->getPlayer();
            endGame = true;
            winnerOptions();

        }else{

            winnerTokens = new ArrayBoard(5,5);
            usedToken = false;
            winnerTokens->appendCard(boardCard);

            int diagonalDown = 1 + recursiveSearch(posMatrixX, posMatrixY, 1, 1,matrixRows, matrixCols, boardCard, 0) + recursiveSearch(posMatrixX, posMatrixY, -1, -1,matrixRows, matrixCols, boardCard, 0);
            if (diagonalDown >= WINNER_ROW){

                winnerPlayer = players->getPlayer();
                endGame = true;
                winnerOptions();

            }else{

                winnerTokens = new ArrayBoard(5,5);
                usedToken = false;
                winnerTokens->appendCard(boardCard);

                int diagonalUp = 1 + recursiveSearch(posMatrixX, posMatrixY, 1, -1,matrixRows, matrixCols, boardCard, 0) + recursiveSearch(posMatrixX, posMatrixY, -1, 1,matrixRows, matrixCols, boardCard, 0);
                if (diagonalUp >= WINNER_ROW){

                    winnerPlayer = players->getPlayer();
                    endGame = true;
                    winnerOptions();

                }else{
                    winnerTokens = new ArrayBoard(5,5);
                }
            }
        }
    }
}

void Game::winnerOptions(){
    winnerPlayer->setWins(winnerPlayer->getWins() + 1);
    if (numberPlayers == MAX_WINS){
        if (winnerPlayer->getWins() == MAX_WINS){
            winnerMenu(true);
        }else{
            winnerMenu();
        }
    }else{
        winnerMenu(true);
    }
}

void Game::changeDiscardImage(BoardCard *boardCard){
    scene->removeItem(discardImage);
    if (boardCard->getValue() >= 0){
        discardImage = new BoardCard(boardCard->getValue(),false, false);
        discardImage->setPosition(20, 350);
        discardImage->setScale(false);
        scene->addItem(discardImage);
    }
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
        try{
            winnerTokens->appendCard(nextCard);
        }catch(std::runtime_error e){}

        if (usedToken && nextCard->getTokenCard()->getPreviousRound()){
            return recursiveSearch(newPosX,newPosY,moveX,moveY,cRows,cCols,nextCard,tokens);
        }
        if (nextCard->getTokenCard()->getPreviousRound() && !usedToken){
            usedToken = true;
            return recursiveSearch(newPosX,newPosY,moveX,moveY,cRows,cCols,nextCard,tokens + 1);
        }
        if (!nextCard->getTokenCard()->getPreviousRound()){
            return recursiveSearch(newPosX,newPosY,moveX,moveY,cRows,cCols,nextCard,tokens + 1);
        }

    }
    if (((newPosX == 0 && newPosY == 0) || (newPosX == 9 && newPosY == 9) ||
        (newPosX == 9 && newPosY == 0) || (newPosX == 0 && newPosY == 9)) && !usedToken){
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
            cardAux->setPosition(positionCardX, positionCardY);
            scene->addItem(cardAux);
        }
    }
}

void Game::defaultSelectedCard(){
    if (selectedHandCard != NULL){
        selectedHandCard->setZValue(0);
        selectedHandCard->defaultPos();
        selectedHandCard->reloadCard();
    }
}

void Game::setSelectedCard(DeckCard* handCard){
    defaultSelectedCard();
    this->selectedHandCard = handCard;
}

void Game::mouseMoveEvent(QMouseEvent* event){
    if (selectedHandCard != NULL){
        selectedHandCard->setSize(40);
        selectedHandCard->setPos(event->pos().x() + 15, event->pos().y() + 15);
    }
    QGraphicsView::mouseMoveEvent(event);
}

void Game::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton && selectedHandCard != NULL){
        selectedHandCard->setZValue(0);
        selectedHandCard->defaultPos();
        selectedHandCard->reloadCard();
        selectedHandCard = NULL;
    }
}

void Game::fillPlayersHand(int maxHandCards){
    players->goToStart();

    for (int i = 0; i < players->getCurrentSize(); i++){
        Player* currentPlayer = players->getPlayer();
        for (int j = 0; j < maxHandCards; j++){
            currentPlayer->drawCard(deck->popCard());
        }
        players->nextPlayer();
    }
}

void Game::discardHands(){
    for (int i = 0; i < players->getCurrentSize(); i++){
        Player* currentPlayer = players->getPlayer();
        int handSize = currentPlayer->getHand()->getCurrentCardSize();
        for (int j = 0; j < handSize; j++){
            DeckCard* cardTemp = currentPlayer->getHand()->popCard();
            discardCards->pushCard(cardTemp);
            changeDiscardImage(cardTemp);
        }
        players->nextPlayer();
    }
}

void Game::resetContinueGame(){
    scene->removeItem(winnerScene);
    scene->removeItem(playerToken);
    scene->removeItem(roundLabel);
    scene->removeItem(playerNameLabel);

    if (winnerPlayer != NULL){
        scene->removeItem(restartGame);

        cleanRound(winnerPlayer);

        for(int i = 0; i < winnerTokens->getCurrentCardSize(); i++){
            winnerTokens->getCard(i)->getTokenCard()->setPreviousRound(true);
        }
        oldWinnerTokens = winnerTokens;

        winnerTokens = new ArrayBoard(5,5);
        endGame = false;
        startRounds();
    }
}

void Game::resetGame(){
    scene->removeItem(winnerScene);
    scene->removeItem(playerToken);
    scene->removeItem(roundLabel);
    scene->removeItem(playerNameLabel);

    if (winnerPlayer != NULL){
        scene->removeItem(exitGame);
        scene->removeItem(newGame);
        scene->removeItem(restartGame);

        cleanRound(winnerPlayer);

        tableBoard->resetBoard(NULL,NULL);


        deck = new ArrayStackDeck(MAX_DECK_CARDS * MAX_DECKS,MAX_DECK_CARDS);
        deck->fillDeck();

        discardHands();

        discardCards = new ArrayStackDeck(MAX_DECK_CARDS * MAX_DECKS,MAX_DECK_CARDS);

        undoPile = new UndoStack();
        redoPile = new UndoStack();

        roundLabel = NULL;

        selectedHandCard = NULL;

        winnerPlayer = NULL;
        oldWinnerTokens = NULL;
        usedToken = false;

        endGame = false;
        winnerTokens = new ArrayBoard(5,5);

        round = 0;

        players->goToStart();

        for (int i = 0; i < players->getCurrentSize(); i++){
            players->getPlayer()->setWins(0);
            players->nextPlayer();
        }

        int maxHandCards = (this->numberPlayers == 4) ? 6 : 7;
        fillPlayersHand(maxHandCards);

        players->goToStart();
        startRounds();
    }
}

void Game::undoFunction(){
    if (undoPile->getSize() > 0){
        Play* lastPlay = undoPile->pop();
        defaultSelectedCard();
        selectedHandCard = NULL;

        cleanRound(players->getPlayer());

        Player* playerTurn = lastPlay->getPlayerTurn();
        players->setPlayer(playerTurn);
        BoardCard* tableCard = lastPlay->getTableCard();

        deck->pushCard(playerTurn->getHand()->removeCard(lastPlay->getDrawedCard()));

        if (lastPlay->getPlayId() == 1){

            if (lastPlay->getWinnerTokens()->getCurrentCardSize() > 0){
                playerTurn->setWins(playerTurn->getWins()-1);

                scene->removeItem(winnerScene);
                scene->removeItem(playerToken);
                scene->removeItem(roundLabel);
                scene->removeItem(playerNameLabel);

                scene->removeItem(exitGame);
                scene->removeItem(newGame);
                scene->removeItem(restartGame);

                winnerPlayer = NULL;

                endGame = false;

                for(int i = 0; i < lastPlay->getWinnerTokens()->getCurrentCardSize(); i++){
                    lastPlay->getWinnerTokens()->getCard(i)->getTokenCard()->setPreviousRound(false);
                }
            }

            tableCard->setOwner(NULL);
            tableCard->reloadCard();

        }else if (lastPlay->getPlayId() == 2){
            tableCard->setOwner(lastPlay->getLastOwner());
            tableCard->reloadCard();
        }else if (lastPlay->getPlayId() == 3){

        }

        DeckCard* handCardTemp = discardCards->popCard();
        playerTurn->drawCard(handCardTemp);
        handCardTemp->reloadCard();

        changeDiscardImage(discardCards->topCard());

        redoPile->push(lastPlay->getPlayId(),round, lastPlay->getDrawedCard(),lastPlay->getPlayedCard(),lastPlay->getTableCard(),playerTurn, lastPlay->getWinnerTokens() ,lastPlay->getLastOwner());

        round = lastPlay->getRound();
        showRound(playerTurn);
    }
}

void Game::redoFunction(){
    // Error en el redo
    if (redoPile->getSize() > 0){
        Play* lastPlay = redoPile->pop();

        selectedHandCard = lastPlay->getPlayedCard();
        round = lastPlay->getRound();
        checkCards(lastPlay->getTableCard(), true);
    }
}



void Game::winnerMenu(bool winner){

    cleanRound(winnerPlayer);

    this->winnerScene = new QGraphicsRectItem();
    winnerScene->setRect(0,WINDOW_HEIGHT/4,WINDOW_WIDTH,WINDOW_HEIGHT/2); // Tamaño de la escena
    winnerScene->setBrush((QBrush(QImage(":/Images/Images/background.jpg")))); // Imagen de fondoe
    winnerScene->setZValue(5);
    scene->addItem(winnerScene);


    playerToken = winnerPlayer->getPlayerToken();
    playerToken->setPos(60,(WINDOW_HEIGHT/4)+40);
    playerToken->setZValue(5);
    scene->addItem(playerToken);

    roundLabel = new QGraphicsTextItem("Is the Winner (u mad bro?)"); // Creamos el label del jugador
    roundLabel->setFont(gameFont); // Seteamos el estilo del titulo
    roundLabel->setPos(400,(WINDOW_HEIGHT/4)+150);
    roundLabel->setZValue(5);
    scene->addItem(roundLabel);

    playerNameLabel = new QGraphicsTextItem(winnerPlayer->getName()); // Creamos el label del jugador
    playerNameLabel->setFont(gameFont); // Seteamos el estilo del titulo
    playerNameLabel->setPos(400,(WINDOW_HEIGHT/4)+100);
    playerNameLabel->setZValue(5);
    scene->addItem(playerNameLabel);
    if (winner){
        restartGame = new Button(QString("restart"));
        restartGame->setPosition(900,(WINDOW_HEIGHT/4)+50);
        connect(restartGame, SIGNAL(clicked()), this, SLOT(resetGame()));
        restartGame->setZValue(5);
        scene->addItem(restartGame);

        newGame = new Button(QString("newgame"));
        newGame->setPosition(900,(WINDOW_HEIGHT/4)+120);
        connect(newGame, SIGNAL(clicked()), this, SLOT(newGameSlot()));
        newGame->setZValue(5);
        scene->addItem(newGame);

        exitGame = new Button(QString("exit"));
        exitGame->setPosition(900,(WINDOW_HEIGHT/4)+190);
        connect(exitGame, SIGNAL(clicked()), this, SLOT(close()));
        exitGame->setZValue(5);
        scene->addItem(exitGame);
    }else{

        restartGame = new Button(QString("continue"));
        restartGame->setPosition(900,(WINDOW_HEIGHT/2)-50);
        connect(restartGame, SIGNAL(clicked()), this, SLOT(resetContinueGame()));
        restartGame->setZValue(5);
        scene->addItem(restartGame);
    }
}


void Game::newGameSlot(){
    scene->removeItem(winnerScene);
    scene->removeItem(playerToken);
    scene->removeItem(roundLabel);
    scene->removeItem(playerNameLabel);

    if (winnerPlayer != NULL){
        scene->clear();
        this->scene = new QGraphicsScene();
        scene->setSceneRect(0,0,WINDOW_WIDTH,WINDOW_HEIGHT); // Tamaño de la escena
        setScene(this->scene); // Añadimos la escena

        selectPlayer();
    }
}
