#include "obstaculos.h"

Obstaculos::Obstaculos(QObject *parent)
    : QObject{parent}
{}

Obstaculos::Obstaculos(short x, short y,short posx, short posy, short ancho, short alto,short movimiento,Personajes *soldado)
{
    this->x=x;
    this->y=y;
    this->posx=posx;
    this->posy=posy;
    this->ancho=ancho;
    this->alto=alto;
    vel=5;
    this->soldado=soldado;
    this->movimiento=movimiento;
    sprite=new QPixmap(":/Imagenes/SpritesaUsar.png");
    setPos(posx,posy);

}

QRectF Obstaculos::boundingRect() const
{
    return QRectF(0,0,ancho,alto);
}

void Obstaculos::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF posicionSprite(x,y,ancho,alto);
    QRectF dibuja(0,0,ancho,alto);
    painter->drawPixmap(dibuja,*sprite,posicionSprite);
}

short Obstaculos::getterPosY()
{
    return posy;
}

short Obstaculos::getterPosX()
{
    return posx;
}

void Obstaculos::moverUp()
{
    posy=posy-vel;
    setPos(posx,posy);
}

void Obstaculos::moverDown()
{
    posy=posy+vel;
    setPos(posx,posy);
}

void Obstaculos::moverRight()
{
    posx=posx+vel;
    setPos(posx,posy);
}

void Obstaculos::moverLeft()
{
    posx=posx-vel;
    setPos(posx,posy);
}


