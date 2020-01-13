#include <QThread>
#include <QMutex>
#include <QImage>
extern "C"
{
    #include "libavformat/avformat.h"
    #include "libswscale/swscale.h"
}
class FFMpeg;

class DecodeThread:public QThread
{
  Q_OBJECT
public:
    DecodeThread();
    void stop();
protected:
    void run();
private:
    bool _stop;
    FFMpeg *mpeg;
};
class FFMpeg
{
public:
    void openVideo(char *path);
    AVPacket ReadFrame();
    void DecodeFrame(const AVPacket *pkt);
    bool YuvToRGB(char *out, int outweight, int outheight);
private:
    QMutex mtx;
    AVFormatContext* m_afc;
    AVFrame *m_yuv;
    SwsContext *m_cCtx;
    int m_videoStream;

};
