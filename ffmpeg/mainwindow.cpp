#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    player = new Mplayer();
    player->setParent(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

