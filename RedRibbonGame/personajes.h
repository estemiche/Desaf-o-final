#ifndef PERSONAJES_H
#define PERSONAJES_H

#include "nivel.h"

class Personajes :public Nivel
{
    Q_OBJECT
public:
    explicit Personajes(QObject *parent = nullptr);
    Personajes(short x,short y,short posx, short posy,short ancho, short alto,short movimiento);
    Personajes(short posx,short posy);
    Personajes(short x,short y,short posx,short posy);
    short vel,movimiento;
    QRectF boundingRect()const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)override;
    void moverUpGoku();
    void moverDownGoku();
    void moverRightGoku();
    void moverLeftGoku();
    void sacarPoderUp();
    void sacarPoderLeft();
    void sacarPoderRight();
    void restablecerGoku();
    void moverUp();
    void moverDown();
    void moverRight();
    void moverLeft();
    void actualizaPuerta();


signals:
public slots:


};

#endif // PERSONAJES_H
