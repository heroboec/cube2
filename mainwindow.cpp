#include <QVBoxLayout>

#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cube.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myCube = new cube;
    cubeImage = QImage(this->width(),this->height(),QImage::Format_RGB32);
    QObject::connect(myCube,SIGNAL(repCube(QImage&)),this,SLOT(repCube(QImage&)));
    QObject::connect(this,SIGNAL(rotate(double,double)),myCube,SLOT(rotate(double,double)));
    myCube->evaluateCube();
}

MainWindow::~MainWindow()
{    
    delete ui;
}


void MainWindow::repCube(QImage& img)
{
    if (cubeImage.size() != img.size())
    {
        cubeImage =  cubeImage.scaled(img.width(),img.height());
    }
    cubeImage = img;
    repaint();
}

void MainWindow::paintEvent(QPaintEvent *pe)
{
    QRectF target(0,0,cubeImage.width(),cubeImage.height());
    QPainter pntr(this);
    pntr.drawImage(target,cubeImage,target);
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left)
    {
        emit rotate(static_cast<double>(10),static_cast<double>(0));
    }

    if (event->key() == Qt::Key_Right)
    {
        emit rotate(static_cast<double>(-10),static_cast<double>(0));
    }

    if (event->key() == Qt::Key_Up)
    {
        emit rotate(static_cast<double>(0),static_cast<double>(10));
    }

    if (event->key() == Qt::Key_Down)
    {
        emit rotate(static_cast<double>(0),static_cast<double>(-10));
    }

    if (event->key() == Qt::Key_End)
    {
        emit rotate(static_cast<double>(7),static_cast<double>(-9));
    }
}
