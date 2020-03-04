#include "VideoProgress.h"
#include <QPainter>
#include <QPen>
//VideoProgress::VideoProgress(unsigned _totalTime,QWidget *parent):QWidget(parent)
//{
//    totalTime = _totalTime;
//    curTime = 0;
//}
void VideoProgress::setProgress(unsigned int timeStamp)
{
    curTime = timeStamp;
}
void VideoProgress::setTotalTime(unsigned int _totalTime)
{
    if(_totalTime!=0)
    {
         totalTime = _totalTime;
    }
}
void VideoProgress::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(QRect(0,0,width()-1,height()-1),Qt::gray);
    int w = ((float)curTime)/totalTime * width();
    painter.fillRect(QRect(0,0,w,height()-1),Qt::green);
    QPen pen(Qt::blue);
    pen.setWidth(3);
    painter.setPen(pen);
    painter.drawLine(w,0,w,height()-1);

}
//VideoProgress::~VideoProgress()
//{

//}
