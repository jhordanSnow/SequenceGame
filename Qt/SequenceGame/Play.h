#ifndef PLAY_H
#define PLAY_H

#include "DeckCard.h"
#include "BoardCard.h"
#include "Player.h"

class Play{
public:
    Play();
    Play(int playId, int round, DeckCard* drawedCard, DeckCard* playedCard, BoardCard* tableCard ,Play* previousPlay = NULL, Play* nextPay = NULL);
    int getPlayId();
    void setPlayId(int value);

    DeckCard *getDrawedCard();
    void setDrawedCard(DeckCard *value);

    Play *getNextPlay();
    void setNextPlay(Play *value);

    Play *getPreviousPlay();
    void setPreviousPlay(Play *value);

    virtual ~Play();
    int getRound();
    void setRound(int value);

private:
    int playId;
    int round;
    DeckCard* drawedCard;
    DeckCard* playedCard;
    BoardCard* tableCard;
    Player* playerTurn;
    Play* nextPlay;
    Play* previousPlay;
};

#endif // PLAY_H
