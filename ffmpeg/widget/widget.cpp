#include "widget.h"
#include<QPainter>
Mplayer::Mplayer()
{
    resize(480,480);
}
extern  char out[];
void Mplayer::paintEvent(QPaintEvent *e)
{
    static QImage *image = nullptr;
    if (image == nullptr)
    {
        //视频是YVU四通道的类型。
        uchar *buf = new uchar[width() * height() * 4];
        image = new QImage(buf, width(), height(), QImage::Format_ARGB32);
    }
    memcpy(image->bits(),out,width() * height() * 4);
    QPainter painter;
    painter.begin(this);
    painter.drawImage(QPoint(0, 0), *image);
    painter.end();
}
