#include <QApplication>
#include "Game.h"

Game* sequence;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Creamos la instancia general del juego
    sequence = new Game();
    sequence->show();
    // Mostramos el menú de inicio del juego
    sequence->mainMenu();

    return a.exec();
}
