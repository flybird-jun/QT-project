_Pragma("once")
#include<QWidget>
class VideoList:public QWidget
{
Q_OBJECT
public:
     VideoList(QWidget *parent =nullptr);
     void paintEvent(QPaintEvent* evt);
     ~VideoList();
};
