#ifndef OBSTACULOS_H
#define OBSTACULOS_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>

class Obstaculos : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit Obstaculos(QObject *parent = nullptr);
    Obstaculos (short x,short y,short posx,short posy,short ancho,short alto);
    short posx,posy,x,y,ancho,alto,vel;
    QPixmap *sprite;
    QRectF boundingRect()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void moverUp();
    void moverDown();
    void moverRight();
    void moverLeft();

signals:
};

#endif // OBSTACULOS_H
