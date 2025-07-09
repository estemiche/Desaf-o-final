#ifndef MUROS_H
#define MUROS_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>

class Muros : public QObject,public QGraphicsItem
{

    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    explicit Muros(QObject *parent = nullptr);
    Muros(short x,short y,short ancho,short alto);
    short posx,posy,x,y,ancho,alto;
    QRectF boundingRect()const;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
    QPixmap *sprite;
signals:
};

#endif // MUROS_H
