#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
ui(new Ui::MainWindow){

    ui->setupUi(this);
    scene = new QGraphicsScene();
    box = new QGraphicsRectItem(0, 0, 10, 10);
    scene->addItem(box);
    ui->graphicsView->setScene(scene);

    phys = Physics();

    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, &MainWindow::timerFire);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateBox);


    timer->start(10);

}

MainWindow::~MainWindow(){
    delete ui;
}


void MainWindow::timerFire(){
    //qDebug() << "timer fired";
    phys.step();
}

void MainWindow::updateBox(){
    qDebug() << "Pos: " << phys.getX() << ", " << phys.getY();
    box->setPos(phys.getX(), phys.getY());
    ui->graphicsView->update();
}
