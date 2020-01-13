#include"decode.h"
char out[480*480*4];
DecodeThread::DecodeThread()
{
    _stop = false;
}
void DecodeThread::run()
{
    mpeg = new FFMpeg();
    mpeg->openVideo("abc.mp4");
    while(1)
      {
        AVPacket pkt = mpeg->ReadFrame();
        mpeg->DecodeFrame(&pkt);
        mpeg->YuvToRGB(out,480,480);
       // mpeg->YuvToRGB(out,480,480);
        sleep(5);
      }
}
void DecodeThread::stop()
{
    _stop = true;
}


void FFMpeg::openVideo(char *path)
{
    mtx.lock();
    int nRet = avformat_open_input(&m_afc, path, 0, 0);

    for (int i = 0; i < m_afc->nb_streams; i++)  //nb_streams打开的视频文件中流的数量，一般nb_streams = 2，音频流和视频流
    {
        AVCodecContext *acc = m_afc->streams[i]->codec; //分别获取音频流和视频流的解码器

        if (acc->codec_type == AVMEDIA_TYPE_VIDEO)   //如果是视频
        {
            m_videoStream = i;
            AVCodec *codec = avcodec_find_decoder(acc->codec_id);   // 查找解码器

            //"没有该类型的解码器"
            if (!codec)
            {
                mtx.unlock();
                return;
            }

            int err = avcodec_open2(acc, codec, NULL); //打开解码器

            if (err != 0)
            {
                //解码器打开失败
            }
        }
    }
    mtx.unlock();
}
AVPacket FFMpeg::ReadFrame()
{
    AVPacket pkt;
    memset(&pkt, 0, sizeof(AVPacket));

    mtx.lock();
    if (!m_afc)
    {
        mtx.unlock();
        return pkt;
    }

    int err = av_read_frame(m_afc, &pkt);
    if (err != 0)
    {
        //失败
    }
    mtx.unlock();

    return  pkt;
}
void FFMpeg::DecodeFrame(const AVPacket *pkt)
{
    mtx.lock();
    if (!m_afc)
    {
        mtx.unlock();
        return;
    }

    if (m_yuv == NULL)
    {
        m_yuv = av_frame_alloc();
    }

    AVFrame *frame = m_yuv;  //指针传值

    int re = avcodec_send_packet(m_afc->streams[pkt->stream_index]->codec, pkt);
    if (re != 0)
    {
        mtx.unlock();
        return;
    }

    re = avcodec_receive_frame(m_afc->streams[pkt->stream_index]->codec, frame);
    if (re != 0)
    {
        //失败
        mtx.unlock();
        return;
    }
    mtx.unlock();
}
bool FFMpeg::YuvToRGB(char *out, int outweight, int outheight)
{
    mtx.lock();
    if (!m_afc || !m_yuv) //像素转换的前提是视频已经打开
    {
        mtx.unlock();
        return false;
    }

    AVCodecContext *videoCtx = m_afc->streams[this->m_videoStream]->codec;
    m_cCtx = sws_getCachedContext(m_cCtx, videoCtx->width, videoCtx->height,
        videoCtx->pix_fmt,  //像素点的格式
        outweight, outheight,  //目标宽度与高度
        AV_PIX_FMT_BGRA,  //输出的格式
        SWS_BICUBIC,  //算法标记
        NULL, NULL, NULL
        );

    if (m_cCtx)
    {
        //sws_getCachedContext 成功"
    }
    else
    {
        //"sws_getCachedContext 失败"
    }

    uint8_t *data[AV_NUM_DATA_POINTERS] = { 0 };

    data[0] = (uint8_t *)out;  //指针传值，形参的值会被改变，out的值一直在变，所以QImage每次的画面都不一样，画面就这样显示出来了，这应该是整个开发过程最难的点
    int linesize[AV_NUM_DATA_POINTERS] = { 0 };
    linesize[0] = outweight * 4;  //每一行转码的宽度

    //返回转码后的高度
    int h = sws_scale(m_cCtx, m_yuv->data, m_yuv->linesize, 0, videoCtx->height,
        data,
        linesize
        );
    mtx.unlock();
}


