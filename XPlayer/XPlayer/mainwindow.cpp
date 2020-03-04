#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    playerStatus = new PlayerStatus(this);
    videoControl = new VideoControl(this);
    videoList = new VideoList(this);
    videoWidget = new VideoWidget(this);

    //先写个固定大小
    resize(800,600);

    playerStatus->resize(800,100);
    playerStatus->move(0,0);

    videoList->resize(100,500);
    videoList->move(0,100);

    videoWidget->resize(700,400);
    videoWidget->move(100,100);



    //背景色
//    QPalette pal(palette());
//    pal.setColor(QPalette::Background,QColor(70,53,53));
//    this->setPalette(pal);
}

MainWindow::~MainWindow()
{
    if(videoWidget)
    {
        delete videoWidget;
        videoWidget = nullptr;
    }
    if(playerStatus)
    {
        delete playerStatus;
        playerStatus = nullptr;
    }
    if(videoList)
    {
        delete videoList;
        videoList = nullptr;
    }
    if(videoControl)
    {
        delete videoControl;
        videoControl = nullptr;
    }
    delete ui;
}

