#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "muros.h"
#include <QGraphicsScene>
#include <QList>
#include <fstream>
#include <iostream>
#include "obstaculos.h"
#include "personajes.h"
#include <QKeyEvent>
#include "nivel.h"
#include <QTimer>

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
    QList <Muros*>muros;
    QList <Obstaculos*>obstaculos;
    QList <Personajes*>personajes;
    QList <Nivel*>corazones;
    QTimer *timer;
    QTimer *timer1;
    Nivel *niveles;
    Personajes *goku;
    void cargarMuros(const QString& nombreArchivo);
    void cargarObjetos(const QString& nombreArchivo);
    void cargarPersonajes(const QString& nombreArchivo);
    void cargarCorazones(const QString& nombreArchivo);
    bool evaluarColisionGokuMuros();
    bool evaluarColisionGokuObstaculos();
    void energia();
    void energiaSoldados();
};
#endif // MAINWINDOW_H
