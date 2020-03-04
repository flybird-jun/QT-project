_Pragma("once")
#include<QToolButton>
#include<QImage>
class VideoButton:public QToolButton
{
Q_OBJECT
public:
     using QToolButton::QToolButton;
     VideoButton(QWidget * parent = nullptr);
     void paintEvent(QPaintEvent *) override;
     void setDownImage(const QImage &img);
     ~VideoButton();
private:
     QColor bgColor;
     QImage *img;
public slots:
    void onClicked();
    void onPress();
    void onRelease();
};
