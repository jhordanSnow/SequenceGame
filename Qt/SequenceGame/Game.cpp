#include "Game.h"

#include <QDebug>

const QString PATH_TOKEN = ":/Tokens/Tokens/"; // Ruta de las cartas
const QString EXT_TOKEN = ".png";

Game::Game(){
    /*
    ** Inicializamos la pantalla
    */
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Eliminamos la barra horizontal
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Eliminamos la barra vertical
    setFixedSize(1200,600); // Le damos un tamaño fijo
    /*
    ** Inicializamos la escena
    */
    this->scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1200,600); // Tamaño de la escena
    setScene(this->scene); // Añadimos la escena

    /*
    ** Inicializamos la lista de los jugadores
    */
    this->players = new CircleListPlayers(6);
}

void Game::loadDeck(){

}

void Game::loadBoard(bool random){}

void Game::mainMenu(){
    scene->clear();
    setBackgroundBrush(QBrush(QImage(":/Images/Images/main.jpg"))); // Imagen de fondo del menú principal

    /*
    ** Creamos el botón de inicio
    */
    Button* select = new Button(QString("start"));
    // Posicionamos el botón en el centro de la pantalla
    int bxPos = this->width()/2 - select->boundingRect().width()/2;
    int byPos = 280;
    select->setPos(bxPos,byPos);
    // Conectamos el botón con la pantalla de selección de jugadores
    connect(select, SIGNAL(clicked()), this, SLOT(selectPlayer())); //cambiar a la seleccion de los jugadores
    scene->addItem(select);

    /*
    ** Creamos el botón de salir
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
    scene->clear();

    setBackgroundBrush(QBrush(QImage(":/Images/Images/background.jpg"))); // Imagen de fondoe

    loadBoard();

    DeckCard* carta3 = new DeckCard(3, "pica", 230, 50);
    setBackgroundBrush(Qt::red);
    scene->addItem(carta3);

}

void Game::selectPlayer(){
    scene->clear();
    setBackgroundBrush(QBrush(QImage(":/Images/Images/select_player.jpg"))); // Imagen de fondo

    /*
    ** Botón de volver al inicio del juego
    */
    Button* back = new Button(QString("back"));
    back->setPos(5,538);
    connect(back, SIGNAL(clicked()), this, SLOT(mainMenu()));
    scene->addItem(back);

    /*
    ** Creamos el botón para la selección de 2 jugadores
    */
    Button* twoPlayers = new Button(QString("2_players"));
    twoPlayers->setPos(570,40);
    scene->addItem(twoPlayers);

    /*
    ** Creamos el botón para la selección de 3 jugadores
    */
    Button* threePlayers = new Button(QString("3_players"));
    threePlayers->setPos(290,220);
    scene->addItem(threePlayers);

    /*
    ** Creamos el botón para la selección de 4 jugadores
    */
    Button* fourPlayers = new Button(QString("4_players"));
    fourPlayers->setPos(570,280);
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
    this->numberPlayers = numberPlayers;
    getPlayer(0);
}

void Game::getPlayer(int playerId){
    scene->clear();
    setBackgroundBrush(QBrush(QImage(":/Images/Images/background.jpg"))); // Imagen de fondo

    if (playerId < numberPlayers){
        QGraphicsTextItem* tituloJuego = new QGraphicsTextItem(QString("Player ") + QString::number(playerId + 1)); // Creamos el label del jugador
        QFont fuenteTitulo("comic sans",30); // Elejimos la fuente y el tamaño
        tituloJuego->setFont(fuenteTitulo); // Seteamos el estilo del titulo
        tituloJuego->setPos(550,310);
        scene->addItem(tituloJuego);

        QLineEdit *playerName = new QLineEdit; // Creamo el objeto en donde se escribe el nombre del jugador
        playerName->setGeometry(550,420,500,50); // Le damos la posición y el tamaño
        scene->addWidget(playerName); // Añadimos el input text a la escena

        QSignalMapper* signalMapper = new QSignalMapper(this);

        /*
        ** Botón del back
        */
        Button* back = new Button(QString("back"));
        back->setPos(5,538);
        int previousPlayer = playerId - 1;


        if (playerId == 0) {
            connect(back, SIGNAL(clicked()), this, SLOT(selectPlayer()));
        }else{
            connect (back, SIGNAL(clicked()), signalMapper, SLOT(map()));
            signalMapper -> setMapping (back, previousPlayer);
            connect (signalMapper, SIGNAL(mapped(int)), this, SLOT(getPlayer(int)));

        }

        scene->addItem(back);

        /*
        ** Botón del next
        */
        Button* next = new Button(QString("next"));
        next->setPos(1050,538);

        connect (next, SIGNAL(clicked()), signalMapper, SLOT(map())) ;
        signalMapper -> setMapping (next, playerId) ;
        connect (signalMapper, SIGNAL(mapped(int)), this, SLOT(addPlayer(int))) ;

        scene->addItem(next);
    }
}

void Game::addPlayer(int playerId){
    players->addPlayer(new Player("player "+QString::number(playerId),"asdasd"));
    playerId++;
    if (playerId == numberPlayers){
        startGame();
    }else{
        getPlayer(playerId);
    }
}


