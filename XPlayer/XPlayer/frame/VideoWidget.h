_Pragma("once")
#include<QWidget>
#include <QThread>
#include "VideoCode/VideoCode.h"
class VideoWidget:public QWidget
{
Q_OBJECT
public:
     VideoWidget(QWidget *parent =nullptr);
     void paintEvent(QPaintEvent* evt);
     ~VideoWidget();
signals:
     void DecodeVideoSignal(char *path);
private:
    QThread * thread;
    VideoCode *videoCode;
    QImage img;
public slots:
    void VideoImageSlots(QImage &image);
};
