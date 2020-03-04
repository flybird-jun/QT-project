#include "VideoButton.h"
#include <QPainter>
VideoButton::VideoButton(QWidget *parent):QToolButton(parent)
{
    bgColor = QColor(116,106,106,25);
    img = nullptr;
    const int buttonWidth = 50;
    const int buttonHeight = 50;
    resize(buttonWidth,buttonHeight);
}
void VideoButton::setDownImage(const QImage &image)
{
    img = new QImage(image);
}
void VideoButton::paintEvent(QPaintEvent *evt)
{
    QPainter painter(this);
    painter.fillRect(QRect(0,0,width(),height()),bgColor);
    QToolButton::paintEvent(evt);
}
void VideoButton::onClicked()
{

}
void VideoButton::onPress()
{
    bgColor = QColor(151,137,137,77);
}
void VideoButton::onRelease()
{
    bgColor = QColor(116,106,106,25);
}
VideoButton::~VideoButton()
{
    if(img == nullptr)
    {
        delete img;
        img = nullptr;
    }
}
