#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QTimer>

#include <random>
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),next_map(NULL),now_map(NULL)
{
    ui->setupUi(this);

    QTimer *timer=new QTimer;
    timer->start();
    timer->setInterval(1);
    connect(timer,SIGNAL(timeout()),this,SLOT(time_count()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::time_count(){

}

void MainWindow::on_rand_but_clicked(){
    if(next_map!=NULL){
        delete next_map;
    }
    next_map=new map;
    ui->next_map->setScene(next_map->getScene());

    ui->map_array->setText(QString::fromStdString(next_map->getMapArray()));

}


void MainWindow::on_copy_but_clicked()
{
    if(next_map==NULL){
        return;
    }
    if(now_map!=NULL){
        delete now_map;
    }
    now_map=next_map;
    next_map=NULL;
    ui->now_map->setScene(now_map->getScene());


}


void MainWindow::on_start_but_clicked()
{
    if(now_map!=NULL){
        now_map->viewShortRoot();
    }
}

