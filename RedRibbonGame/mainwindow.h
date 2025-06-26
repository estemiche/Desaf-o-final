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
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    short x,y,ancho,alto;
    QList <Muros*>muros;
    QList <Obstaculos*>obstaculos;
    QList <Personajes*>personajes;
    void cargarMuros(const QString& nombreArchivo);
    void cargarObjetos(const QString& nombreArchivo);
    void cargarPersonajes(const QString& nombreArchivo);
};
#endif // MAINWINDOW_H
