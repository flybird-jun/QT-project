#include "frame/VideoList.h"
#include <QPainter>
VideoList::VideoList(QWidget * parent):QWidget(parent)
{

}
void VideoList::paintEvent(QPaintEvent *evt)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.drawRect(rect());
}
VideoList::~VideoList()
{

}
