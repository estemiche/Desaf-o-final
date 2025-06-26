#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    x=0;
    y=0;
    ancho=900;
    alto=900;
    scene=new QGraphicsScene(x,y,ancho,alto);
    ui->graphicsView->setScene(scene);
    cargarMuros("Nivel1.txt");
    cargarObjetos("Obstaculos.txt");
    cargarPersonajes("Personajes.txt");
}
void MainWindow::cargarMuros(const QString& nombreArchivo)
{
    std::ifstream archivo(nombreArchivo.toStdString());
    if (!archivo.is_open()){
        std::cerr<<"El archivo no abrio";
    }
    short x,y,w,h;
    while (archivo>>x>>y>>w>>h){
        muros.append(new Muros(x,y,w,h));
        scene->addItem(muros.back());
    }
    archivo.close();
}

void MainWindow::cargarObjetos(const QString &nombreArchivo)
{
    std::ifstream archivo(nombreArchivo.toStdString());
    if(!archivo.is_open()){
        std::cerr<<"El archivo no abrio";
    }
    short x,y,posx,posy,w,h;
    while (archivo>>x>>y>>posx>>posy>>w>>h){
        obstaculos.append(new Obstaculos(x,y,posx,posy,w,h));
        scene->addItem(obstaculos.back());
    }
    archivo.close();
}

void MainWindow::cargarPersonajes(const QString &nombreArchivo)
{
    std::ifstream archivo(nombreArchivo.toStdString());
    if(!archivo.is_open()){
        std::cerr<<"El archivo no abrio";
    }
    short x,y,posx,posy,w,h;
    while (archivo>>x>>y>>posx>>posy>>w>>h){
        personajes.append(new Personajes(x,y,posx,posy,w,h));
        scene->addItem(personajes.back());
    }
    archivo.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_W){
        personajes[0]->moverUp();
    }
    else if (event->key()==Qt::Key_S){
        personajes[0]->moverDown();
    }
    else if (event->key()==Qt::Key_D){
        personajes[0]->moverRight();
    }
    else if (event->key()==Qt::Key_A){
        personajes[0]->moverLeft();
    }
}

