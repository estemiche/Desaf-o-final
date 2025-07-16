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
    iniciado=false;
    vel=5;
    velx=1;
    vely=1;
    gravedad=9.8;
    tiempo=0.4;
    angulo= (3.141596*5)/180;
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

void Obstaculos::calcularVelocidad()
{
    velx=vel*cos(angulo);
    vely=vel*sin(angulo);
}

void Obstaculos::calcularPosicion()
{
    posx=posx+velx*tiempo;
    posy=posy-vely*tiempo+0.5*gravedad*tiempo*tiempo;
    setPos(posx,posy);
}
void Obstaculos::calcularPosicionInversa()
{
    posx=posx-velx*tiempo;
    posy=posy-vely*tiempo+0.5*gravedad*tiempo*tiempo;
    setPos(posx,posy);
}

void Obstaculos::actualizarVelocidad()
{
    vel=sqrt(pow(velx,2)+pow(vely,2));
    angulo=atan2(vely,velx);
}



