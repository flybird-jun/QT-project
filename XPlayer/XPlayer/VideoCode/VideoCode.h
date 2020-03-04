#include<QThread>
#include <QImage>
class VideoCode:public QObject
{
    Q_OBJECT
public:
    void Delay(unsigned int msecs);
public slots:
    void DecodeVideo(char * path);
signals:
    void showImage(QImage& img);
    void TotalTimeSignal(unsigned int sec);
};
