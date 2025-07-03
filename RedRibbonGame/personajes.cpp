#include "personajes.h"

Personajes::Personajes(QObject *parent)
    : QObject{parent}
{
    x=0;
    y=0;
    posx=430;
    posy=630;
    ancho=25;
    alto=43;
    vel=2;
    energia=100;
    sprite=new QPixmap(":/imagenes/SpritesaUsar.png");
    timer=new QTimer();
    timer->start(800);
    connect(timer,&QTimer::timeout,this,&Personajes::renewGoku);
    setPos(posx,posy);

}

Personajes::Personajes(short x, short y, short posx, short posy, short ancho, short alto)
{
    this->x=x;
    this->y=y;
    this->posx=posx;
    this->posy=posy;
    this->ancho=ancho;
    this->alto=alto;
    vel=2;
    sprite=new QPixmap(":/imagenes/SpritesaUsar.png");
    setPos(posx,posy);
}

void Personajes::renewGoku()
{
    x+=ancho;
    if (x>=ancho*2){
        x=0;
    }
    this->update();
}
QRectF Personajes::boundingRect() const
{
    return QRectF(0,0,ancho,alto);
}

void Personajes::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF posicionSprite(x,y,ancho,alto);
    QRectF dibuja(0,0,ancho,alto);
    painter->drawPixmap(dibuja,*sprite,posicionSprite);
}

void Personajes::moverUp()
{
    posy=posy-vel;
    setPos(posx,posy);

}

void Personajes::moverDown()
{
    posy=posy+vel;
    setPos(posx,posy);
    x+=50;
    if(x>=100){
        x=50;
    }
    update();
}

void Personajes::moverRight()
{
    posx=posx+vel;
    setPos(posx,posy);
    x+=ancho*4;
    if(x>=ancho*6){
        x=ancho*4;
    }
    update();
}

void Personajes::moverLeft()
{
    posx=posx-vel;
    setPos(posx,posy);
    x+=ancho*6;
    if(x>=ancho*8){
        x=ancho*6;
    }
    update();
}

