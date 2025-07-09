#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
        goku->moverUp();

        if(evaluarColisionGokuMuros()){
            goku->moverDown();
        }
        if(evaluarColisionGokuObstaculos()){
            energia();

        }
    }
    else if(event->key()==Qt::Key_S){
        goku->restablecerGoku();
        goku->moverDown();
        if(evaluarColisionGokuMuros()){
            goku->moverUp();

        }
        if(evaluarColisionGokuObstaculos()){
            energia();

        }

    }
    else if(event->key()==Qt::Key_D){
        goku->restablecerGoku();
        goku->moverRight();

        if(evaluarColisionGokuMuros()){
            goku->moverLeft();

        }
        if(evaluarColisionGokuObstaculos()){
            energia();
        }
    }
    else if(event->key()==Qt::Key_A){
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
            if(obst->posx>800){
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
            if(obst->posx>800){
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
                pers->moverRightSold();
                }
            if(pers->posx>300){
                    pers->x=27;
            }
            if(pers->x==27){
                pers->moverLeftSold();
            }
            if(pers->posx<100){
                pers->x=0;
            }
            if(pers->x==0){
                pers->moverRightSold();
            }

             break;
        }
        case 2:{
            if(pers->x==28 && pers->y==85 ){
                pers->moverLeftSold();
            }
            if(pers->posx<580){
                pers->x=0;
            }
            if(pers->x==0){
                pers->moverRightSold();
            }
            if(pers->posx>700){
                pers->x=28;
            }
            if(pers->x==28){
                pers->moverLeftSold();
            }
            break;
        }
        case 3:{
            if(pers->x==53 && pers->y==85 ){
                pers->moverRightSold();
            }
            if(pers->posx>90){
                pers->x=81;
            }
            if(pers->x==81){
                pers->moverLeftSold();
            }
            if(pers->posx<50){
                pers->x=53;
            }
            if(pers->x==53){
                pers->moverRightSold();
            }
            break;
        }
        case 4:{
            if(pers->x==81 && pers->y==85 ){
                pers->moverLeftSold();
            }
            if(pers->posx<780){
                pers->x=53;
            }
            if(pers->x==53){
                pers->moverRightSold();
            }
            if(pers->posx>820){
                pers->x=81;
            }
            if(pers->x==81){
                pers->moverLeftSold();
            }
            break;
        }

        case 5:{
            if(pers->x==0 && pers->y==85 ){
                pers->moverRightSold();
            }
            if(pers->posx>260){
                pers->x=28;
            }
            if(pers->x==28){
                pers->moverLeftSold();
            }
            if(pers->posx<180){
                pers->x=0;
            }
            if(pers->x==0){
                pers->moverRightSold();
            }
            break;
        }

        case 6:{
            if(pers->x==28 && pers->y==85 ){
                pers->moverLeftSold();
            }
            if(pers->posx<580){
                pers->x=0;
            }
            if(pers->x==0){
                pers->moverRightSold();
            }
            if(pers->posx>630){
                pers->x=28;
            }
            if(pers->x==28){
                pers->moverLeftSold();
            }
            break;
        }

        case 7:{
            if(pers->x==53 && pers->y==85 ){
                pers->moverRightSold();
            }
            if(pers->posx>380){
                pers->x=81;
            }
            if(pers->x==81){
                pers->moverLeftSold();
            }
            if(pers->posx<320){
                pers->x=53;
            }
            if(pers->x==53){
                pers->moverRightSold();
            }
            break;
        }
        case 8:{
            if(pers->x==81 && pers->y==85 ){
                pers->moverLeftSold();
            }
            if(pers->posx<500){
                pers->x=53;
            }
            if(pers->x==53){
                pers->moverRightSold();
            }
            if(pers->posx>560){
                pers->x=81;
            }
            if(pers->x==81){
                pers->moverLeftSold();
            }
            break;
        }
        case 9:{
            if(pers->energia==100 && evaluarColisionGokuPersonajes()){
                pers->x=0;
                pers->y=130;
                goku->moverDown();
            }
            if(pers->energia=50 && evaluarColisionGokuPersonajes()){
                pers->x=34;
                pers->y=130;
                goku->moverDown();
            }
            if(pers->energia==0 && evaluarColisionGokuPersonajes()){
                pers->x=67;
                pers->y=130;
            }
            break;
        }

        default:
            break;
        }

    }
}





void MainWindow::energia()
{
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
        scene1->addText("GAMEOVER");
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

        for (int i = 0; i < obstaculos.count(); ++i) {
            if(goku->collidesWithItem(obstaculos[i])){
                scene1->removeItem(obstaculos[i]);
                obstaculos.removeAt(i);
            }

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
    for(auto muro : muros) delete muro;
    for(auto person: personajes) delete person;
    for(auto obst: obstaculos) delete obst;
    for(auto cora: corazones) delete cora;
}
