#ifndef OBSTACULOS_H
#define OBSTACULOS_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>
#include "personajes.h"


class Obstaculos : public QObject,public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit Obstaculos(QObject *parent = nullptr);
    Obstaculos(short x,short y,short posx,short posy,short ancho,short alto,short movimiento,Personajes *soldado);
    short posx,posy,x,y,ancho,alto,vel,movimiento;
    QPixmap *sprite;
    QRectF boundingRect()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void moverUp();
    void moverDown();
    void moverRight();
    void moverLeft();
    Personajes *soldado;


signals:
};

#endif // OBSTACULOS_H
