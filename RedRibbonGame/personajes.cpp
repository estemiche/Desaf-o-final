#include "personajes.h"

Personajes::Personajes(QObject *parent)
    : QObject{parent}
{}

Personajes::Personajes(short x, short y, short posx, short posy, short ancho, short alto)
{
    this->x=x;
    this->y=y;
    this->posx=posx;
    this->posy=posy;
    this->ancho=ancho;
    this->alto=alto;
    vel=3;
    sprite=new QPixmap(":/imagenes/SpritesaUsar.png");
}

QRectF Personajes::boundingRect() const
{
    return QRectF(posx,posy,ancho,alto);
}

void Personajes::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF posicionSprite(x,y,ancho,alto);
    QRectF dibuja(posx,posy,ancho,alto);
    painter->drawPixmap(dibuja,*sprite,posicionSprite);
}

void Personajes::moverUp()
{
    posy=posy-vel;
    setPos(posx,posy);
    update();
}

void Personajes::moverDown()
{
    posy=posy+vel;
    setPos(posx,posy);
    update();
}

void Personajes::moverRight()
{
    posx=posx+vel;
    setPos(posx,posy);
    update();
}

void Personajes::moverLeft()
{
    posx=posx-vel;
    setPos(posx,posy);
    update();
}
