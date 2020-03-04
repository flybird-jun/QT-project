_Pragma("once")
#include<QWidget>
class VideoProgress:public QWidget
{
    Q_OBJECT
public:
      using QWidget::QWidget;
     //VideoProgress(unsigned _totalTime,QWidget *parent=nullptr);
     void setProgress(unsigned int timeStamp);
     void setTotalTime(unsigned _totalTime);
    // ~VideoProgress();
     void paintEvent(QPaintEvent *event);
private:
     unsigned int totalTime;
     unsigned curTime;
signals:
    void moveProgress(unsigned int timeStamp);
};
