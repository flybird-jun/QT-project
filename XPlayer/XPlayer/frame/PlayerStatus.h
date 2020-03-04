_Pragma("once")
#include<QWidget>
class PlayerStatus:public QWidget
{
Q_OBJECT
public:
     PlayerStatus(QWidget *parent =nullptr);
     void paintEvent(QPaintEvent* evt);
     ~PlayerStatus();
};
