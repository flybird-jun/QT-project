#include "frame/VideoWidget.h"
#include <QPainter>

VideoWidget::VideoWidget(QWidget * parent):QWidget(parent)
{
    thread = new QThread();
    videoCode = new VideoCode();
    videoCode->moveToThread(thread);
    thread->start();
    connect(this,&VideoWidget::DecodeVideoSignal,videoCode,&VideoCode::DecodeVideo);
    connect(videoCode,&VideoCode::showImage,this,&VideoWidget::VideoImageSlots,Qt::BlockingQueuedConnection);
    emit DecodeVideoSignal("5.avi");
}
void VideoWidget::paintEvent(QPaintEvent *evt)
{
    QPainter painter(this);
    painter.drawImage(QPoint(0,0),img);
  //  painter.setPen(Qt::black);
   // painter.drawRect(rect());
}
 void VideoWidget::VideoImageSlots(QImage &image)
 {
    img = image;
    repaint();
 }
VideoWidget::~VideoWidget()
{
    if(thread)
    {
        thread->terminate();
        thread->wait();
        delete thread;
    }
    if(videoCode)
    {
        delete videoCode;
    }
}
