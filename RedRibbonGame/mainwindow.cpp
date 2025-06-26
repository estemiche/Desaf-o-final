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
    cargarMuros("Muros.txt");
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

MainWindow::~MainWindow()
{
    delete ui;
}

