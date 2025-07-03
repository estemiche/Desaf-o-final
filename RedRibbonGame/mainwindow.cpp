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
    niveles=new Nivel();
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
        goku->moverUp();
        if(evaluarColisionGokuMuros()){
            goku->moverDown();
        }
        if(evaluarColisionGokuObstaculos()){
            goku->moverDown();
            energia();
        }
    }
    else if (event->key()==Qt::Key_S){
        goku->moverDown();
        if(evaluarColisionGokuMuros()){
            goku->moverUp();
        }
        if(evaluarColisionGokuObstaculos()){
            goku->moverUp();
            energia();
        }
    }
    else if (event->key()==Qt::Key_D){
        goku->moverRight();

        if(evaluarColisionGokuMuros()){
            goku->moverLeft();
        }
        if(evaluarColisionGokuObstaculos()){
            goku->moverLeft();
            energia();
        }
    }
    else if (event->key()==Qt::Key_A){
        goku->moverLeft();

        if(evaluarColisionGokuMuros()){
            goku->moverRight();
        }
        if(evaluarColisionGokuObstaculos()){
            goku->moverRight();
            energia();
        }
    }
}


void MainWindow::disparo()
{
   obstaculos[3]->moverRight();
    if(obstaculos[3]->posx>450){
       obstaculos[3]->posx=260;
    }
   obstaculos[4]->moverLeft();
    if(obstaculos[4]->posx<490){
       obstaculos[4]->posx=630;
    }
    obstaculos[5]->moverDown();
    if(obstaculos[5]->posy>600){
        obstaculos[5]->posy=450;
    }
    obstaculos[6]->moverDown();
    if(obstaculos[6]->posy>600){
        obstaculos[6]->posy=450;
    }
    obstaculos[7]->moverRight();
    if(obstaculos[7]->posx>380){
        obstaculos[7]->posx=230;
    }
    obstaculos[8]->moverLeft();
    if(obstaculos[8]->posx<460){
        obstaculos[8]->posx=610;
    }
    obstaculos[9]->moverRight();
    obstaculos[9]->moverDown();
    if(obstaculos[9]->posx>480){
       obstaculos[9]->posx=330;
        obstaculos[9]->posy=200;
    }
    obstaculos[10]->moverLeft();
    obstaculos[10]->moverDown();
    if(obstaculos[10]->posx<410){
        obstaculos[10]->posx=560;
        obstaculos[10]->posy=210;
    }
    obstaculos[2]->moverLeft();
    obstaculos[2]->moverDown();
    if(obstaculos[2]->posx<460){
        obstaculos[2]->posx=710;
        obstaculos[2]->posy=410;
    }
    obstaculos[1]->moverRight();
    obstaculos[1]->moverDown();
    if(obstaculos[1]->posx>425){
        obstaculos[1]->posx=175;
        obstaculos[1]->posy=410;
    }
    obstaculos[13]->moverRight();
    obstaculos[13]->moverUp();
    if(obstaculos[13]->posx>410){
        obstaculos[13]->posx=320;
        obstaculos[13]->posy=500;
    }
    obstaculos[14]->moverLeft();
    obstaculos[14]->moverUp();
    if(obstaculos[14]->posx<430){
        obstaculos[14]->posx=530;
        obstaculos[14]->posy=500;
    }
    if(evaluarColisionGokuObstaculos()){
        energia();
    }
}

void MainWindow::energia()
{
    if(gokuInvulnerable) return;
    goku->energia-=20;
    goku->setOpacity(1);
    niveles->cambiaEnergia();
    if(goku->energia==0){
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


