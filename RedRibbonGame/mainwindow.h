#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "muros.h"
#include <QGraphicsScene>
#include <QList>
#include <fstream>
#include <iostream>

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

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    short x,y,ancho,alto;
    QList <Muros*>muros;
    void cargarMuros(const QString& nombreArchivo);
};
#endif // MAINWINDOW_H
