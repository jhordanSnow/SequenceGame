#ifndef PLAYER_H
#define PLAYER_H

#include <QString>

class Player{
public:
    Player(QString name, QString urlToken);
private:
    QString name;
    QString urlToken;
};

#endif // PLAYER_H