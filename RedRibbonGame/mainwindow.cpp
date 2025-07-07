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
    timer=new QTimer();
    timer->start(200);
    connect(timer,&QTimer::timeout,this,&MainWindow::disparo);
    timer1=new QTimer();
    timer1->start(200);
    connect(timer1,&QTimer::timeout,this,&MainWindow::animarSoldados);
    niveles=new Nivel;
    goku=new Personajes;
    scene1->addItem(niveles);
    niveles->setPos(720,80);
    scene1->addItem(goku);
    cargarMuros("Nivel1.txt");
    cargarObjetos("Obstaculos.txt");
    cargarPersonajes("Personajes.txt");
    cargarCorazones("Nivel.txt");
    gokuInvulnerable=false;
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

bool MainWindow::evaluarColisionGokuMuros()
{
    for(int i=0;i<muros.count();i++){
        if(goku->collidesWithItem(muros[i])){
            return true;
        }
    }
    return false;
}

bool MainWindow::evaluarColisionGokuObstaculos()
{
    for(int i = 0;i<obstaculos.count();++i){
        if(goku->collidesWithItem(obstaculos[i]) || obstaculos[i]->collidesWithItem(goku))
            return true;
    }
    return false;
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_W){
        goku->restablecerGoku();
        goku->moverUp();
        if(evaluarColisionGokuMuros()){
            goku->moverDown();
        }
        if(evaluarColisionGokuObstaculos()){
            energia();
        }
    }
    else if (event->key()==Qt::Key_S){
        goku->restablecerGoku();
        goku->moverDown();
        if(evaluarColisionGokuMuros()){
            goku->moverUp();
        }
        if(evaluarColisionGokuObstaculos()){
            energia();
        }
    }
    else if (event->key()==Qt::Key_D){
        goku->restablecerGoku();
        goku->moverRight();

        if(evaluarColisionGokuMuros()){
            goku->moverLeft();
        }
        if(evaluarColisionGokuObstaculos()){
            energia();
        }
    }
    else if (event->key()==Qt::Key_A){
        goku->restablecerGoku();
        goku->moverLeft();

        if(evaluarColisionGokuMuros()){
            goku->moverRight();
        }
        if(evaluarColisionGokuObstaculos()){
            energia();
        }
    }
    else if(event->key()==Qt::Key_Z){
        goku->sacarPoderLeft();
        energiaSoldados();
    }
    else if(event->key()==Qt::Key_X){
        goku->restablecerGoku();
        goku->sacarPoderRight();
        energiaSoldados();
    }
    else if(event->key()==Qt::Key_Q){
        goku->sacarPoderUp();
        energiaSoldados();
    }
}


void MainWindow::disparo()
{
    obstaculos[0]->moverLeft();
    obstaculos[0]->moverDown();
    if(obstaculos[0]->posx<460){
        obstaculos[0]->posx=710;
        obstaculos[0]->posy=410;
    }
    obstaculos[1]->moverRight();
    obstaculos[1]->moverDown();
    if(obstaculos[1]->posx>425){
        obstaculos[1]->posx=175;
        obstaculos[1]->posy=410;
    }
    obstaculos[5]->moverRight();
    obstaculos[5]->moverUp();
    if(obstaculos[5]->posx>410){
        obstaculos[5]->posx=320;
        obstaculos[5]->posy=500;
    }
    obstaculos[4]->moverLeft();
    obstaculos[4]->moverUp();
    if(obstaculos[4]->posx<430){
        obstaculos[4]->posx=530;
        obstaculos[4]->posy=500;
    }
    if(evaluarColisionGokuObstaculos()){
        energia();
    }
}

void MainWindow::animarSoldados()
{
 for (int i = 0; i < personajes.count(); ++i) {
        if(personajes[i]->x==0 && personajes[i]->y==85){
            personajes[i]->x=27;
            personajes[i]->y=85;
        }
        if(personajes[i]->x==28 && personajes[i]->y==85){
            personajes[i]->x=0;
            personajes[i]->y=85;
        }
        if (personajes[i]->x==53 && personajes[i]->y==85){
            personajes[i]->x=81;
            personajes[i]->y=85;
        }

        if(personajes[i]->x==81 && personajes[i]->y==85){
            personajes[i]->x=53;
            personajes[i]->y=85;
        }
        personajes[i]->update();
 }
}

void MainWindow::energia()
{
    if(gokuInvulnerable) return;
    goku->energia-=20;
    goku->setOpacity(1);
    niveles->cambiaEnergia();
    if(goku->energia==0 &&!corazones.empty()){
            scene1->removeItem(corazones.last());
            corazones.pop_back();
            goku->energia=100;
        }
    if(corazones.empty()){
        scene1->setBackgroundBrush(Qt::red);
        scene1->addText("GAME OVER");
        scene1->removeItem(niveles);
        delete niveles;
    }
    gokuInvulnerable=true;
    goku->setOpacity(0.5);
    QTimer::singleShot(2000,this,[=](){
        gokuInvulnerable=false;
        goku->setOpacity(1.0);
    });
}

void MainWindow::energiaSoldados()
{
    for(int e = personajes.count() - 1; e >= 0; --e){
        if(goku->collidesWithItem(personajes[e])){
            personajes[e]->energia -= 50;
            if(personajes[e]->energia <= 0){
                scene1->removeItem(personajes[e]);
                personajes.removeAt(e);
            }
        }
    }

    for (int i = 0; i<obstaculos.count();++i) {
        if(goku->collidesWithItem(obstaculos[i])){
            scene1->removeItem(obstaculos[i]);
            obstaculos.removeAt(i);
            i--;
        }

    }
}
MainWindow::~MainWindow()
{
    delete ui;
    delete scene1;
    delete timer;
    delete niveles;
    delete goku;
    for(auto muro: muros)delete muro;
    for(auto person: personajes)delete person;
    for(auto obst: obstaculos)delete obst;
    for(auto cora: corazones)delete cora;
}


