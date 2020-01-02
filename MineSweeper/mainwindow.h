#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "chess.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    ChessWidget * chess;
public slots:
    void newGameSlots();
    void actionEasySlots();
    void actionNormalSlots();
    void actionDiffcultSlots();

    void winGame();
    void lossGame();
public:
    MainWindow(QWidget *parent = nullptr);
    void newGame();
    ~MainWindow();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
