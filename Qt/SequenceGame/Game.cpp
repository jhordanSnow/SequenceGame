#include "Game.h"

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
    //scene->setBackgroundBrush(Qt::blue); // Color de fondo
    setScene(this->scene); // Añadimos la escena
}

void Game::mainMenu(){
    scene->clear();
    setBackgroundBrush(QBrush(QImage(":/Images/Images/main.jpg"))); // Imagen de fondo del menú principal

    QGraphicsTextItem* tituloJuego = new QGraphicsTextItem(QString("SEQUENCE")); // Creamos el titulo del menú
    QFont fuenteTitulo("comic sans",30); // Elejimos la fuente y el tamaño
    tituloJuego->setFont(fuenteTitulo); // Seteamos el estilo del titulo
    int txPos = this->width()/2 - tituloJuego->boundingRect().width()/2;
    int tyPos = 150;
    tituloJuego->setPos(txPos,tyPos);
    scene->addItem(tituloJuego);
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

    DeckCard* carta3 = new DeckCard(3, "pica", 230, 50);
    setBackgroundBrush(Qt::red);
    scene->addItem(carta3);
}

void Game::selectPlayer(){
    scene->clear();
    setBackgroundBrush(QBrush(QImage(":/Images/Images/select_player.jpg"))); // Imagen de fondo

    Button* back = new Button(QString("back"));
    back->setPos(5,538);
    connect(back, SIGNAL(clicked()), this, SLOT(mainMenu()));
    scene->addItem(back);


    Button* twoPlayers = new Button(QString("2_players"));
    twoPlayers->setPos(570,40);
    connect(twoPlayers, SIGNAL(clicked()), this, SLOT(createPlayer()));
    scene->addItem(twoPlayers);

    Button* threePlayers = new Button(QString("3_players"));
    threePlayers->setPos(290,220);
    //connect(threePlayers, SIGNAL(clicked()), this, SLOT(createPlayer(3))); //cambiar a la seleccion de los jugadores
    scene->addItem(threePlayers);

    Button* fourPlayers = new Button(QString("4_players"));
    fourPlayers->setPos(570,280);
    //connect(fourPlayers, SIGNAL(clicked()), this, SLOT(createPlayer(4))); //cambiar a la seleccion de los jugadores
    scene->addItem(fourPlayers);
}

void Game::createPlayer(){
    int numberPlayers = 2;
    scene->clear();

    Button* back = new Button(QString("back"));
    back->setPos(5,538);
    connect(back, SIGNAL(clicked()), this, SLOT(selectPlayer()));
    scene->addItem(back);

    setBackgroundBrush(QBrush(QImage(":/Images/Images/background.jpg"))); // Imagen de fondo
    for (int i = 1; i <= numberPlayers; i++){

    }
}


