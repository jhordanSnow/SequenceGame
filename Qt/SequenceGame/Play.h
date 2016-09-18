#ifndef PLAY_H
#define PLAY_H

#include "DeckCard.h"
#include "BoardCard.h"
#include "Player.h"
#include "ArrayBoard.h"

class Play{
public:
    Play();
    Play(int playId, int round, DeckCard* drawedCard, DeckCard* playedCard, BoardCard* tableCard , Player* playerTurn, Player* lastOwner, ArrayBoard* winnerTokens  = NULL, Play* previousPlay = NULL);
    int getPlayId();
    void setPlayId(int value);

    DeckCard *getDrawedCard();
    void setDrawedCard(DeckCard *value);

    Play *getNextPlay();
    void setNextPlay(Play *value = NULL);

    Play *getPreviousPlay();
    void setPreviousPlay(Play *value = NULL);

    virtual ~Play();
    int getRound();
    void setRound(int value);

    BoardCard *getTableCard();
    void setTableCard(BoardCard *value);

    DeckCard *getPlayedCard();
    void setPlayedCard(DeckCard *value);

    Player *getPlayerTurn();
    void setPlayerTurn(Player *value);

    void removeNextPlay();
    Player *getLastOwner();
    void setLastOwner(Player *value);

    ArrayBoard *getWinnerTokens();
    void setWinnerTokens(ArrayBoard *value);

private:
    int playId;
    int round;
    DeckCard* drawedCard;
    DeckCard* playedCard;
    BoardCard* tableCard;
    Player* playerTurn;
    Player* lastOwner;
    Play* nextPlay;
    Play* previousPlay;

    ArrayBoard *winnerTokens;
};

#endif // PLAY_H
