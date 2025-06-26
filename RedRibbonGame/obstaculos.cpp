#include "obstaculos.h"

Obstaculos::Obstaculos(QObject *parent)
    : QObject{parent}
{}

Obstaculos::Obstaculos(short x, short y,short posx,short posy,short ancho,short alto)
{
    this->x=x;
    this->y=y;
    this->posx=posx;
    this->posy=posy;
    this->ancho=ancho;
    this->alto=alto;
    sprite=new QPixmap(":/imagenes/SpritesaUsar.png");
}
QRectF Obstaculos::boundingRect() const
{
    return QRectF(posx,posy,ancho,alto);
}

void Obstaculos::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF posicionSprite(x,y,ancho,alto);
    QRectF dibuja(posx,posy,ancho,alto);
    painter->drawPixmap(dibuja,*sprite,posicionSprite);
}

