#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "frame/PlayerStatus.h"
#include "frame/VideoControl.h"
#include "frame/VideoList.h"
#include "frame/VideoWidget.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    PlayerStatus *playerStatus = nullptr;
    VideoControl *videoControl=nullptr;
    VideoList *videoList=nullptr;
    VideoWidget *videoWidget=nullptr;
public:
   // void paintEvent(QPaintEvent* evt);
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
