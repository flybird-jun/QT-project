#include "frame/VideoControl.h"
#include <QPainter>
VideoControl::VideoControl(QWidget * parent):QWidget(parent)
{

    resize(700,100);
    move(100,500);

    QPalette pal(palette());
    pal.setColor(QPalette::Window,Qt::black);
    setAutoFillBackground(true);

    //设置按键大小，位置

    const int gap = 10;
    const int leftGap = 20;
    int x = leftGap;


    previous = new VideoButton(this);
    previous->setIcon(QIcon(":/image/previous.png"));

    int y = (height()-previous->height())/2;

    int y1 = height();
    int y2 = previous->height();

    previous->move(x,y);

    x+= previous->width()+gap;
    run = new VideoButton(this);
    run->setIcon(QIcon(":/image/run.png"));
    run->move(x,y);

    x+= run->width()+gap;
    next = new VideoButton(this);
    next->setIcon(QIcon(":/image/next.png"));
    next->move(x,y);

    progress = new VideoProgress(this);
    progress->move(200,40);
    progress->resize(300,20);


   // progress->setTotalTime(500);
   // progress->setProgress(100);
}
void VideoControl::TotalTimeSlot(unsigned int sec)
{
    progress->setTotalTime(sec);
}
void VideoControl::paintEvent(QPaintEvent *evt)
{
    QPainter painter(this);
    QPen linePen;
    linePen.setWidth(30);
    linePen.setColor(Qt::black);
    painter.setPen(linePen);
    painter.drawLine(QPoint(0,0),QPoint(width(),0));

}
VideoControl::~VideoControl()
{
    if(run)
    {
        delete run;
        run = nullptr;
    }
    if(next)
    {
        delete next;
        next = nullptr;
    }
    if(previous)
    {
        delete previous;
        previous = nullptr;
    }
    if(voice)
    {
        delete voice;
        voice = nullptr;
    }
    if(progress)
    {
        delete voice;
        voice = nullptr;
    }
}
