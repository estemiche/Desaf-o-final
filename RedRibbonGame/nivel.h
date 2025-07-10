#ifndef NIVEL_H
#define NIVEL_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>
#include <QTimer>



class Nivel : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit Nivel(QObject *parent = nullptr);
    Nivel(short x,short y,short posx,short posy,short ancho,short alto);
    short x,y,posx,posy,ancho,alto;
    short energia,vida;
    QTimer *timer;
    QPixmap *sprite;
    QRectF boundingRect()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void cambiaEnergia();



signals:

};

#endif // NIVEL_H
