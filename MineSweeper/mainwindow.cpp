#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "item.h"
#include "ItemType.h"
#include <QPainter>
#include "messageBox.h"
#include <QIcon>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //菜单栏
    connect(ui->menu,&QMenu::aboutToShow,this,&MainWindow::newGameSlots);
    connect(ui->actioneasy,&QAction::triggered,this,&MainWindow::actionEasySlots);
    connect(ui->actionnormal,&QAction::triggered,this,&MainWindow::actionNormalSlots);
    connect(ui->actiondiffcult,&QAction::triggered,this,&MainWindow::actionDiffcultSlots);

    //棋盘
   // chess = new ChessWidget(10,10,30,this);
    chess = new ChessWidget(20,20,30,this);
    initChess();


}
void MainWindow::newGameSlots()
{
    newGame();
}
void MainWindow::initChess()
{
     chess->move(5,ui->menubar->height()+2);
     chess->setVisible(true);
     connect(chess,&ChessWidget::GameWin,this,&MainWindow::winGame);
     connect(chess,&ChessWidget::GameLoss,this,&MainWindow::lossGame);

     resize(chess->width()+10,chess->height()+ui->menubar->height()+5);
}
void MainWindow::newGame()
{
    chess->releaseItems();
    chess->initItems();
    initChess();
    chess->repaint();
}
void MainWindow::actionEasySlots()
{
    delete chess;
    chess = new ChessWidget(10,10,30,this);
    initChess();
    repaint();
}
void MainWindow::actionNormalSlots()
{
    delete chess;
    chess = new ChessWidget(15,15,30,this);
    initChess();
    repaint();
}
void MainWindow::actionDiffcultSlots()
{
    chess->setParent(nullptr);
    delete chess;
    chess = new ChessWidget(20,20,30,this);
    repaint();
}
void MainWindow::winGame()
{
    int ret;
    QMessageBox *box = new QMessageBox(this);
    box->setText("你赢了");
    box->setWindowIcon(QIcon(":/win.png"));
    ret = box->exec();
    if(ret == 0)
    {
        newGame();
    }
    else
    {
        chess->disconnect();
    }
}
void MainWindow::lossGame()
{
    int ret;
    QMessageBox *box = new MessageBox(this);
    box->setText("你输了");
    box->setWindowIcon(QIcon(":/loss.png"));
    ret = box->exec();
    if(ret == 0)
    {
        newGame();
    }
    else
    {
        chess->disconnect();
    }

}
MainWindow::~MainWindow()
{
    delete ui;
    delete chess;
}

