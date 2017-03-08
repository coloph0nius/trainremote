#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QtNetwork>
#include <QDebug>

int temp=0;
double velo=0;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->slider1->setRange(-100,100);
    ui->slider2->setRange(-100,100);
    ui->slider3->setRange(-100,100);
    ui->slider4->setRange(-100,100);
    ui->slider5->setRange(-100,100);

    ui->slider1->setValue(0);
    ui->slider2->setValue(0);
    ui->slider3->setValue(0);
    ui->slider4->setValue(0);
    ui->slider5->setValue(0);


    connect(ui->slider1, SIGNAL (valueChanged(int)), this, SLOT(display1(int)));
    connect(ui->speed1plus, SIGNAL (clicked()), this, SLOT(increase1()) );
    connect(ui->speed1minus, SIGNAL (clicked()), this, SLOT(decrease1()) );
    connect(ui->stop1, SIGNAL (clicked()), this, SLOT(halt1()) );

    connect( ui->actionBeenden, SIGNAL (triggered()), this, SLOT(close()));

    udpSocket = new QUdpSocket(this);
    connect(ui->slider1, SIGNAL(valueChanged(int)),this, SLOT(sendDatagram(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::display1(int i)
{
    ui->speed1->display(i);
}


void MainWindow::increase1()
{
    temp=ui->speed1->intValue();
    temp+=5;
    if (temp>=100)
            temp=100;
    //ui->speed1->display(temp);
    ui->slider1->setValue(temp);
}

void MainWindow::decrease1()
{
    temp=ui->speed1->intValue();
    temp-=5;
    if (temp<=-100)
            temp=-100;
    //ui->speed1->display(temp);
    ui->slider1->setValue(temp);
}

void MainWindow::halt1()
{
    ui->slider1->setValue(0);
}

void MainWindow::sendDatagram(int i)
{
    QByteArray datagram;
    char buffer [10];
    velo=(i*0.01)*1023;
    i=velo;
    if (i>0){
        sprintf(buffer, "2;%i",i);
        datagram.append(buffer);
        qDebug()<<"datagram sent: "<<i<<" "<<datagram;
    }
    else if (i<0){
        i*=-1;
        sprintf(buffer, "1;%i",i);
        datagram.append(buffer);
        qDebug()<<"datagram sent: "<<i<<" "<<datagram;
    }
    else{
       datagram="0;0";
       qDebug()<<"datagram sent: "<<datagram;
    }
    udpSocket->writeDatagram(datagram.data(), datagram.size(),QHostAddress("192.168.178.36"), 4210);
}

