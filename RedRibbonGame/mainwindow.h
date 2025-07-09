#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <fstream>
#include <iostream>
#include <QKeyEvent>
#include <QTimer>
#include "muros.h"
#include "obstaculos.h"
#include "personajes.h"
#include "nivel.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void keyPressEvent(QKeyEvent *event);
    void disparo();
   void animarSoldados();
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene1;
    short x,y,ancho,alto;
    bool gokuInvulnerable;
    QTimer *timer;
    QTimer *timer1;
    QList <Muros*> muros;
    QList <Obstaculos*>obstaculos;
    QList <Personajes*>personajes;
    QList <Nivel*>corazones;
    Nivel *niveles;
    Personajes *goku;
    void cargarMuros(const QString& nombreArchivo);
    void cargarObjetos(const QString& nombreArchivo);
    void cargarPersonajes(const QString& nombreArchivo);
    void cargarCorazones(const QString& nombreArchivo);
    bool evaluarColisionGokuMuros();
    bool evaluarColisionGokuObstaculos();
    bool evaluarColisionGokuPersonajes();
    void energia();
    void energiaSoldados();


};
#endif // MAINWINDOW_H
