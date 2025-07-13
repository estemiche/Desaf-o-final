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
    short vel,movimiento;
    QRectF boundingRect()const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)override;
    void moverUp();
    void moverDown();
    void moverRight();
    void moverLeft();
    void sacarPoderUp();
    void sacarPoderLeft();
    void sacarPoderRight();
    void restablecerGoku();
    void moverUpSold();
    void moverDownSold();
    void moverRightSold();
    void moverLeftSold();


signals:
public slots:


};

#endif // PERSONAJES_H
