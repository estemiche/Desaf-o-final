#include "muros.h"

Muros::Muros(QObject *parent)
    : QObject{parent}
{}

Muros::Muros(short x, short y, short ancho, short alto)
{
    this->x=64;
    this->y=284;
    this->posx=0;
    this->posy=0;
    this->ancho=ancho;
    this->alto=alto;
    sprite= new QPixmap(":/imagenes/SpritesaUsar.png");
    setPos(x,y);

}

QRectF Muros::boundingRect() const
{
    return QRectF(posx,posy,ancho,alto);
}

void Muros::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF posicionSprite(x,y,ancho,alto);
    QRectF dibuja(posx,posy,ancho,alto);
    painter->drawPixmap(dibuja,*sprite,posicionSprite);
}
