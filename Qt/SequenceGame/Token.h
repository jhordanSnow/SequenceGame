#ifndef TOKEN_H
#define TOKEN_H

#include <QString>
#include <QGraphicsPixmapItem>

class Token:  public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Token(int tokenId);
    void changeToken(int newId);
    int getTokenId();
    void setTokenId(int tokenId);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
signals:
    void clicked();
private:
    int tokenId;
};

#endif // TOKEN_H
