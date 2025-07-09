#ifndef PERSONAJES_H
#define PERSONAJES_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>

class Personajes : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit Personajes(QObject *parent = nullptr);
    Personajes(short x,short y,short posx, short posy,short ancho, short alto,short movimiento);
    short x,y,posx,posy,ancho,alto,vel,energia,movimiento;
    QPixmap *sprite;
    QRectF boundingRect()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
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
