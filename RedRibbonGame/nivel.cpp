#include "nivel.h"

Nivel::Nivel(QObject *parent)
    : QObject{parent}
{
    energia=100;
    x=0;
    y=0;
    ancho=100;
    alto=40;
    sprite= new QPixmap(":/Imagenes/SpritesaUsar1.png");
}

Nivel::Nivel(short x, short y,short posx,short posy,short ancho, short alto)
{
    this->x=x;
    this->y=y;
    this->posx=posx;
    this->posy=posy;
    this->ancho=ancho;
    this->alto=alto;
    sprite= new QPixmap(":/Imagenes/SpritesaUsar.png");
    setPos(posx,posy);
}



QRectF Nivel::boundingRect() const
{
    return QRectF(0,0,ancho,alto);
}

void Nivel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF posicionSprite(x,y,ancho,alto);
    QRectF dibuja(0,0,ancho,alto);
    painter->drawPixmap(dibuja,*sprite,posicionSprite);
}

void Nivel::cambiaEnergia()
{

    if(x<600){
        x+=ancho;
        update();
    }
    if(x>=500){
        x=0;
        update();
    }

}


