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

    for (int i = 0; i < m_afc->nb_streams; i++)  //nb_streams�򿪵���Ƶ�ļ�������������һ��nb_streams = 2����Ƶ������Ƶ��
    {
        AVCodecContext *acc = m_afc->streams[i]->codec; //�ֱ��ȡ��Ƶ������Ƶ���Ľ�����

        if (acc->codec_type == AVMEDIA_TYPE_VIDEO)   //�������Ƶ
        {
            m_videoStream = i;
            AVCodec *codec = avcodec_find_decoder(acc->codec_id);   // ���ҽ�����

            //"û�и����͵Ľ�����"
            if (!codec)
            {
                mtx.unlock();
                return;
            }

            int err = avcodec_open2(acc, codec, NULL); //�򿪽�����

            if (err != 0)
            {
                //��������ʧ��
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
        //ʧ��
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

    AVFrame *frame = m_yuv;  //ָ�봫ֵ

    int re = avcodec_send_packet(m_afc->streams[pkt->stream_index]->codec, pkt);
    if (re != 0)
    {
        mtx.unlock();
        return;
    }

    re = avcodec_receive_frame(m_afc->streams[pkt->stream_index]->codec, frame);
    if (re != 0)
    {
        //ʧ��
        mtx.unlock();
        return;
    }
    mtx.unlock();
}
bool FFMpeg::YuvToRGB(char *out, int outweight, int outheight)
{
    mtx.lock();
    if (!m_afc || !m_yuv) //����ת����ǰ������Ƶ�Ѿ���
    {
        mtx.unlock();
        return false;
    }

    AVCodecContext *videoCtx = m_afc->streams[this->m_videoStream]->codec;
    m_cCtx = sws_getCachedContext(m_cCtx, videoCtx->width, videoCtx->height,
        videoCtx->pix_fmt,  //���ص�ĸ�ʽ
        outweight, outheight,  //Ŀ������߶�
        AV_PIX_FMT_BGRA,  //����ĸ�ʽ
        SWS_BICUBIC,  //�㷨���
        NULL, NULL, NULL
        );

    if (m_cCtx)
    {
        //sws_getCachedContext �ɹ�"
    }
    else
    {
        //"sws_getCachedContext ʧ��"
    }

    uint8_t *data[AV_NUM_DATA_POINTERS] = { 0 };

    data[0] = (uint8_t *)out;  //ָ�봫ֵ���βε�ֵ�ᱻ�ı䣬out��ֵһֱ�ڱ䣬����QImageÿ�εĻ��涼��һ���������������ʾ�����ˣ���Ӧ�������������������ѵĵ�
    int linesize[AV_NUM_DATA_POINTERS] = { 0 };
    linesize[0] = outweight * 4;  //ÿһ��ת��Ŀ��

    //����ת���ĸ߶�
    int h = sws_scale(m_cCtx, m_yuv->data, m_yuv->linesize, 0, videoCtx->height,
        data,
        linesize
        );
    mtx.unlock();
}


