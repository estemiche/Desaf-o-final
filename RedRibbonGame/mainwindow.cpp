#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene1=new QGraphicsScene(0,0,900,750);
    ui->graphicsView->setScene(scene1);
    scene1->setBackgroundBrush(Qt::black);
    niveles=new Nivel();
    goku=new Personajes;
    scene1->addItem(niveles);
    niveles->setPos(720,80);
    scene1->addItem(goku);
    goku->setPos(430,630);
    cargarMuros("Nivel1.txt");
    cargarObjetos("Obstaculos.txt");
    cargarPersonajes("Personajes.txt");
    cargarCorazones("Nivel.txt");
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
        scene1->addItem(muros.back());
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
        scene1->addItem(obstaculos.back());
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
        scene1->addItem(personajes.back());
    }
    archivo.close();
}

void MainWindow::cargarCorazones(const QString &nombreArchivo)
{
    std::ifstream archivo(nombreArchivo.toStdString());
    if(!archivo.is_open()){
        std::cerr<<"El archivo no abrio";
    }
    short x,y,posx,posy,w,h;
    while(archivo>>x>>y>>posx>>posy>>w>>h){
        corazones.append(new Nivel(x,y,posx,posy,w,h));
        scene1->addItem(corazones.back());
    }
    archivo.close();
}

bool MainWindow::evaluarColision()
{
    for(int i=0;i<muros.count();i++){
        if(goku->collidesWithItem(muros[i])){
            return true;
        }
    }
    return false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_W){
        goku->moverUp();
        if(evaluarColision()){
            goku->moverDown();
        }
    }
    else if (event->key()==Qt::Key_S){
        goku->moverDown();
        if(evaluarColision()){
            goku->moverUp();
        }
        }
    else if (event->key()==Qt::Key_D){
        goku->moverRight();
        if(evaluarColision()){
            goku->moverLeft();
    }
        }
    else if (event->key()==Qt::Key_A){
        goku->moverLeft();
        if(evaluarColision()){
            goku->moverRight();
    }
        }
}


