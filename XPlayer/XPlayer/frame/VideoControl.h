_Pragma("once")
#include<QWidget>
#include "VideoButton.h"
#include "VideoProgress.h"
class VideoControl:public QWidget
{
Q_OBJECT
public:
     VideoControl(QWidget *parent =nullptr);
     void paintEvent(QPaintEvent* evt);
     ~VideoControl();
private:
    VideoButton *run;
    VideoButton *next;
    VideoButton *previous;
    VideoButton *voice = nullptr;
    VideoProgress *progress;
public slots:
    void TotalTimeSlot(unsigned int sec);
};
