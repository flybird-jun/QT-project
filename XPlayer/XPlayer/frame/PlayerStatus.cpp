#include "frame/PlayerStatus.h"
#include <QPainter>
PlayerStatus::PlayerStatus(QWidget * parent):QWidget(parent)
{

}
void PlayerStatus::paintEvent(QPaintEvent *evt)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.drawRect(rect());
}
PlayerStatus::~PlayerStatus()
{

}
