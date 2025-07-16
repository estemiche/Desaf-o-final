#ifndef OBSTACULOS_H
#define OBSTACULOS_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>
#include <math.h>
#include "personajes.h"


class Obstaculos : public QObject,public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit Obstaculos(QObject *parent = nullptr);
    Obstaculos(short x,short y,short posx,short posy,short ancho,short alto,short movimiento,Personajes *soldado);
    short x,y,ancho,alto,movimiento;
    double gravedad,angulo,tiempo,velx,vely,posx,posy,vel;
    bool iniciado;
    QPixmap *sprite;
    QRectF boundingRect()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void moverUp();
    void moverDown();
    void moverRight();
    void moverLeft();
    void calcularVelocidad();
    void calcularPosicion();
    void calcularPosicionInversa();
    void actualizarVelocidad();
    Personajes *soldado;


signals:
};

#endif // OBSTACULOS_H
