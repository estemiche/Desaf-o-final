#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    nivelActual=1;
    scene1= new QGraphicsScene(0,0,900,750);
    ui->graphicsView->setScene(scene1);
    scene1->setBackgroundBrush(Qt::black);
    timer=new QTimer();
    timer->start(50);
    connect(timer,&QTimer::timeout,this,&MainWindow::disparo);
    timer1=new QTimer();
    timer1->start(100);
    connect(timer1,&QTimer::timeout,this,&MainWindow::animarSoldados);
    niveles=new Nivel;
    goku=new Personajes;
    puerta1= new Personajes(0,130,416,355);
    puerta2= new Personajes(0,130,432,-5);
    scene1->addItem(puerta1);
    scene1->addItem(puerta2);
    scene1->addItem(niveles);
    niveles->setPos(720,80);
    scene1->addItem(goku);
    cargarMuros("Nivel1.txt");
    cargarPersonajes("Personajes.txt");
    cargarObjetos("Obstaculos.txt");
    cargarCorazones("Nivel.txt");
    gokuInvulnerable=false;

}



void MainWindow::cargarMuros(const QString& nombreArchivo)
{
    std::ifstream archivo(nombreArchivo.toStdString());
    if(!archivo.is_open()){
        std::cerr<<"Archivo no abrio";
    }
    short x,y,w,h;
    while(archivo>>x>>y>>w>>h){
        muros.append(new Muros(x,y,w,h));
        scene1->addItem(muros.back());
    }
    archivo.close();
}

void MainWindow::cargarObjetos(const QString &nombreArchivo)
{
    std::ifstream archivo(nombreArchivo.toStdString());
    if(!archivo.is_open()){
        std::cerr<<"Archivo no abrio";
    }
    short x,y,posx,posy,w,h,movi,indiceS;
    while(archivo>>x>>y>>posx>>posy>>w>>h>>movi>>indiceS){
        if(indiceS>=0 && indiceS<personajes.count()){
            Personajes *soldado=personajes[indiceS];
            Obstaculos *bala=new Obstaculos(x,y,posx,posy,w,h,movi,soldado);
            obstaculos.append(bala);
            scene1->addItem(bala);
        }
        else {
            std::cerr << "Índice fuera de rango: " << indiceS << std::endl;
        }
    }

    archivo.close();
}

void MainWindow::cargarPersonajes(const QString &nombreArchivo)
{
    std::ifstream archivo(nombreArchivo.toStdString());
    if(!archivo.is_open()){
        std::cerr<<"Archivo no abrio";
    }
    short x,y,posx,posy,w,h,movi;
    while(archivo>>x>>y>>posx>>posy>>w>>h>>movi){
        personajes.append(new Personajes(x,y,posx,posy,w,h,movi));
        scene1->addItem(personajes.back());
    }
    archivo.close();
}

void MainWindow::cargarCorazones(const QString &nombreArchivo)
{
    std::ifstream archivo(nombreArchivo.toStdString());
    if(!archivo.is_open()){
        std::cerr<<"Archivo no abrio";
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
    for(int i=0;i<obstaculos.count();++i){
        if(goku->collidesWithItem(obstaculos[i]) || obstaculos[i]->collidesWithItem(goku))
            return true;
    }
    return false;
}

bool MainWindow::evaluarColisionGokuPersonajes()
{
    for (int i = 0; i < personajes.count(); ++i) {
        if(goku->collidesWithItem(personajes[i]) || personajes[i]->collidesWithItem(goku))
            return true;
    }
    return false;
}




void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_W){
        goku->restablecerGoku();
        goku->moverUpGoku();

        if(evaluarColisionGokuMuros()){
            goku->moverDownGoku();
        }
        if(evaluarColisionGokuObstaculos()){
            energia();

        }
    }
    else if(event->key()==Qt::Key_S){
        goku->restablecerGoku();
        goku->moverDownGoku();
        if(evaluarColisionGokuMuros()){
            goku->moverUpGoku();

        }
        if(evaluarColisionGokuObstaculos()){
            energia();

        }

    }
    else if(event->key()==Qt::Key_D){
        goku->restablecerGoku();
        goku->moverRightGoku();

        if(evaluarColisionGokuMuros()){
            goku->moverLeftGoku();

        }
        if(evaluarColisionGokuObstaculos()){
            energia();
        }
    }
    else if(event->key()==Qt::Key_A){
        goku->restablecerGoku();
        goku->moverLeftGoku();
        if(evaluarColisionGokuMuros()){
            goku->moverRightGoku();
        }
        if(evaluarColisionGokuObstaculos()){
            energia();
        }
    }
    else if(event->key()==Qt::Key_Z){
        goku->sacarPoderLeft();
        energiaSoldados();
        destruPuerta();
        energiaBlack();
    }
    else if(event->key()==Qt::Key_X){
        goku->restablecerGoku();
        goku->sacarPoderRight();
        energiaSoldados();
        destruPuerta();
        energiaBlack();
    }
    else if(event->key()==Qt::Key_Q){
        goku->sacarPoderUp();
        energiaSoldados();
        destruPuerta();
        energiaBlack();
    }
    else if(event->key()==Qt::Key_T){
        nivel2();
    }

}

void MainWindow::disparo()
{
    for (int i = 0; i < obstaculos.size(); ++i) {
        Obstaculos *obst=obstaculos[i];
        switch (obst->movimiento) {
        case 0:{
            obst->moverLeft();
            obst->moverDown();
            if(obst->posx<460){
                obst->posx=710;
                obst->posy=410;
            }

            break;
        }
        case 1:{
            obst->moverRight();
            obst->moverDown();
            if(obst->posx>425){
                obst->posx=175;
                obst->posy=410;
            }
            break;
        }
        case 2:{
            obst->moverRight();
            obst->moverUp();
            if(obst->posx>410){
                obst->posx=320;
                obst->posy=500;
            }
            break;
        }
        case 3:{
            obst->moverLeft();
            obst->moverUp();
            if(obst->posx<430){
                obst->posx=530;
                obst->posy=500;
            }
            break;
        }
        case 4:{
            obst->moverRight();
            if(obst->posx>700){
                obst->posx=320;

            }
            break;
        }
        case 5:{
            obst->moverLeft();
            if(obst->posx<100){
                obst->posx=530;

            }
            break;
        }
        case 6:{
            obst->moverDown();
            if(obst->posy>580){
                obst->posy=460;
            }
            break;
        }

        case 7:{
            obst->moverDown();
            if(obst->posy>580){
                obst->posy=460;
            }
            break;
        }
        case 8:{
            obst->moverRight();
            if(obst->posx>750){
                obst->posx=230;
            }
            break;
        }
        case 9:{
            obst->moverLeft();
            if(obst->posx<100){
                obst->posx=610;
            }
            break;
        }
        case 10:{
            obst->moverRight();
            obst->moverDown();
            if(obst->posx>500){
                obst->posx=330;
                obst->posy=210;
            }
            break;
        }
        case 11:{
            obst->moverLeft();
            obst->moverDown();
            if(obst->posx<440){
                obst->posx=560;
                obst->posy=210;
            }
            break;
        }
        case 12:{
            obst->moverRight();
            if(obst->posx>680){
                obst->posx=500;
            }
            break;
        }
        case 13:{
            obst->moverRight();
            if(obst->posx>490){
                obst->posx=300;
            }
            break;
        }
        case 14:{
            obst->moverRight();
            obst->moverDown();
            if(obst->posx>350){
                obst->posx=80;
                obst->posy=100;
            }
            break;
        }
        case 15:{
            obst->moverLeft();
            obst->moverDown();
            if(obst->posx<400){
                obst->posx=760;
                obst->posy=100;
            }
            break;
        }
        case 16:{
            obst->moverRight();
            obst->moverUp();
            if(obst->posx>350){
                obst->posx=100;
                obst->posy=440;
            }
            break;
        }
        case 17:{
            obst->moverLeft();
            obst->moverUp();
            if(obst->posx<500){
                obst->posx=760;
                obst->posy=365;
            }
            break;
        }
        default:
            break;
        }
        if(evaluarColisionGokuObstaculos()){
            energia();
        }
    }
}

void MainWindow::animarSoldados()
{
    for (int i = 0; i < personajes.size(); ++i) {
        Personajes *pers=personajes[i];
        switch (pers->movimiento) {
        case 0:{
            break;
        }
        case 1:{
            if(pers->x==0 && pers->y==85 ){
                pers->moverRight();
            }
            if(pers->posx>300){
                pers->x=27;
            }
            if(pers->x==27){
                pers->moverLeft();
            }
            if(pers->posx<100){
                pers->x=0;
            }
            if(pers->x==0){
                pers->moverRight();
            }

            break;
        }
        case 2:{
            if(pers->x==28 && pers->y==85 ){
                pers->moverLeft();
            }
            if(pers->posx<580){
                pers->x=0;
            }
            if(pers->x==0){
                pers->moverRight();
            }
            if(pers->posx>730){
                pers->x=28;
            }
            if(pers->x==28){
                pers->moverLeft();
            }
            break;
        }
        case 3:{
            if(pers->x==53 && pers->y==85 ){
                pers->moverRight();
            }
            if(pers->posx>90){
                pers->x=81;
            }
            if(pers->x==81){
                pers->moverLeft();
            }
            if(pers->posx<50){
                pers->x=53;
            }
            if(pers->x==53){
                pers->moverRight();
            }
            break;
        }
        case 4:{
            if(pers->x==81 && pers->y==85 ){
                pers->moverLeft();
            }
            if(pers->posx<780){
                pers->x=53;
            }
            if(pers->x==53){
                pers->moverRight();
            }
            if(pers->posx>820){
                pers->x=81;
            }
            if(pers->x==81){
                pers->moverLeft();
            }
            break;
        }

        case 5:{
            if(pers->x==0 && pers->y==85 ){
                pers->moverRight();
            }
            if(pers->posx>260){
                pers->x=28;
            }
            if(pers->x==28){
                pers->moverLeft();
            }
            if(pers->posx<180){
                pers->x=0;
            }
            if(pers->x==0){
                pers->moverRight();
            }
            break;
        }

        case 6:{
            if(pers->x==28 && pers->y==85 ){
                pers->moverLeft();
            }
            if(pers->posx<580){
                pers->x=0;
            }
            if(pers->x==0){
                pers->moverRight();
            }
            if(pers->posx>750){
                pers->x=28;
            }
            if(pers->x==28){
                pers->moverLeft();
            }
            break;
        }

        case 7:{
            if(pers->x==53 && pers->y==85 ){
                pers->moverRight();
            }
            if(pers->posx>380){
                pers->x=81;
            }
            if(pers->x==81){
                pers->moverLeft();
            }
            if(pers->posx<320){
                pers->x=53;
            }
            if(pers->x==53){
                pers->moverRight();
            }
            break;
        }
        case 8:{
            if(pers->x==81 && pers->y==85 ){
                pers->moverLeft();
            }
            if(pers->posx<500){
                pers->x=53;
            }
            if(pers->x==53){
                pers->moverRight();
            }
            if(pers->posx>560){
                pers->x=81;
            }
            if(pers->x==81){
                pers->moverLeft();
            }
            break;
        }
        case 9:{
            if(pers->x==0 && pers->y==85){
                pers->moverRight();
            }
            if(pers->posx>710){
                pers->x=27;
            }
            if(pers->x==27){
                pers->moverLeft();
            }
            if(pers->posx<510){
                pers->x=0;
            }
            if(pers->x==0){
                pers->moverRight();
            }
            break;
        }
        case 10:{
            if(pers->x==28 && pers->y==85){
                pers->moverLeft();
            }
            if(pers->posx<220){
                pers->x=0;
            }
            if(pers->x==0){
                pers->moverRight();
            }
            if(pers->posx>520){
                pers->x=28;
            }
            if(pers->x==28){
                pers->moverLeft();
            }
            break;
        }

        default:
            break;
        }

    }
}

void MainWindow::moverBlack()
{
    if(!black)return;
    if(black->posx<=60){
        black->moverRight();
    }
    else if(black->posx>=790){
        black->moverLeft();
    }
    else if(black->posy<=80){
        black->moverDown();
    }
    else if(black->posy>=410){
        black->moverUp();
    }
    switch(black->movimiento=rand()%8){
    case 0:{
        if(black->x==0 && black->y==181){
            black->moverDown();
            black->moverLeft();
        }
        break;
    }
    case 1:{
        if(black->x==0 && black->y==181){
            black->moverDown();
            black->moverRight();
        }
        break;
    }
    case 2:{
        if(black->x==0 && black->y==181){
            black->moverUp();
            black->moverLeft();
        }
        break;
    }
    case 3:{
        if(black->x==0 && black->y==181){
            black->moverUp();
            black->moverRight();
        }
        break;
    }
    case 4:{
        if(black->x==0 && black->y==181){
            black->moverUp();
        }
        break;
    }
    case 5:{
        if(black->x==0 && black->y==181){
            black->moverDown();
        }
        break;
    }
    case 6:{
        if(black->x==0 && black->y==181){
            black->moverLeft();
        }
        break;
    }
    case 7:{
        if(black->x==0 && black->y==181){
            black->moverRight();
        }
        break;
    }
    default:
        break;
    }
}


void MainWindow::energia()
{
    if(!niveles)return;
    if(gokuInvulnerable) return;
    goku->energia-=20;
    goku->setOpacity(1);
    niveles->cambiaEnergia();
    if(goku->energia==0&&!corazones.empty()){
        scene1->removeItem(corazones.last());
        corazones.pop_back();
        goku->energia=100;

    }
    if(corazones.empty()){
        scene1->setBackgroundBrush(Qt::red);
        texto = scene1->addText("GAMEOVER");
        texto->setDefaultTextColor(Qt::black);
        texto->setFont(QFont("Arial",10, QFont::Bold));
        texto->setScale(5);
        texto->setPos(250,400);
        scene1->removeItem(niveles);
        delete niveles;
        niveles=nullptr;
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
    for(int e=0;e<personajes.count();++e){
        if(goku->collidesWithItem(personajes[e])){
            personajes[e]->energia-=5;
        }
        if(personajes[e]->energia<=0){
            Personajes *soldadoMuerto=personajes[e];

            for (int i = 0; i<obstaculos.count();++i) {
                if(obstaculos[i]->soldado==soldadoMuerto){
                    scene1->removeItem(obstaculos[i]);
                    delete obstaculos[i];
                    obstaculos.removeAt(i);
                    i--;
                }
            }
            scene1->removeItem(soldadoMuerto);
            delete soldadoMuerto;
            personajes.removeAt(e);
            e--;
        }

    }
}

void MainWindow::energiaPuertas()
{
    if(puerta1 && goku->collidesWithItem(puerta1)){
        puerta1->energia-=5;
        goku->moverDownGoku();
    }
    if(puerta2 && goku->collidesWithItem(puerta2)){
        puerta2->energia-=5;
        goku->moverDownGoku();
    }
    if(puerta1 && puerta1->energia==0){
    scene1->removeItem(puerta1);
        delete puerta1;
        puerta1=nullptr;
    }
    else if(puerta2 && puerta2->energia==0){
        scene1->removeItem(puerta2);
        delete puerta2;
        puerta2=nullptr;
    }
    if(personajes.isEmpty() && (!puerta1 || puerta1->energia==0) && (!puerta2 || puerta2->energia==0)){
        nivel2();
    }
}

void MainWindow::energiaBlack()
{
    if(nivelActual!=2 || !black)return;
    if(goku->collidesWithItem(black)){
        black->energia-=1;
    }
    if(black->energia<=0 && black){
        if(timer2){
            timer2->stop();
            delete timer2;
            timer2=nullptr;
        }

    scene1->removeItem(black);
    delete black;
    black=nullptr;
    }
}

void MainWindow::nivel2()
{
    nivelActual=2;
    scene1->clear();
    muros.clear();
    obstaculos.clear();
    personajes.clear();

    corazones.clear();

    scene1->setSceneRect(0,0,900,750);
    scene1->setBackgroundBrush(Qt::darkCyan);

    black=new Personajes(0,181,500,200);
    scene1->addItem(black);
    timer2=new QTimer();
    timer2->start(50);
    connect(timer2,&QTimer::timeout,this,&MainWindow::moverBlack);
    goku=new Personajes(770,550);
    niveles = new Nivel;
    scene1->addItem(niveles);
    scene1->addItem(goku);
    goku->setPos(770,550);
    niveles->setPos(880,80);

    cargarMuros("Muros2.txt");
    cargarCorazones("Nivel2.txt");
    cargarPersonajes("Personajes2.txt");
    cargarObjetos("Obstaculos2.txt");

    gokuInvulnerable=false;
}

void MainWindow::destruPuerta()
{
    if(nivelActual!=1)return;
    if(puerta1 && goku->collidesWithItem(puerta1)){
        puerta1->actualizaPuerta();
        energiaPuertas();
    }
    if(puerta2 && goku->collidesWithItem(puerta2)){
        puerta2->actualizaPuerta();
        energiaPuertas();
    }
}





MainWindow::~MainWindow()
{
    delete ui;
    delete scene1;
    delete timer;
    delete niveles;
    delete goku;
    for(auto muro : muros) delete muro;
    for(auto person: personajes) delete person;
    for(auto obst: obstaculos) delete obst;
    for(auto cora: corazones) delete cora;
}
