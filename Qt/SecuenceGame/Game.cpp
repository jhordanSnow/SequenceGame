#include "Game.h"

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
    setBackgroundBrush(QBrush(QImage(":/Images/Images/main.jpg"))); // Imagen de fondo
    //scene->setBackgroundBrush(Qt::blue); // Color de fondo
    setScene(this->scene); // Añadimos la escena
}

void Game::mainMenu(){
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
    Button* jugar = new Button(QString("start"));
    // Posicionamos el botón en el centro de la pantalla
    int bxPos = this->width()/2 - jugar->boundingRect().width()/2;
    int byPos = 280;
    jugar->setPos(bxPos,byPos);
    // Conectamos el botón con la pantalla de selección de jugadores
    connect(jugar, SIGNAL(clicked()), this, SLOT(startGame())); //cambiar a la seleccion de los jugadores
    scene->addItem(jugar);

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
}

void Game::pickCard(){
    qInfo("Drag");
}
