#include"ItemType.h"
#include<QPainter>
#include<QWidget>
#include<QFont>
QRect ItemType::rect()
{
    return _rect;
}
void ItemType::__mousePressEvent(QMouseEvent *evt)
{
    if(evt->button()==Qt::LeftButton)
    {
        if(!iEmit)
        {
            emitSignal();
            iEmit = true;
        }
    }
}
NumItem::NumItem(QRect irect,int num):ItemType(irect)
{
    this->num = num;
}
void NumItem::emitSignal()
{
    emit pressNumItem();
}
void NumItem::show(QWidget *pwidget)
{
    QPainter paint(pwidget);
    paint.setPen(Qt::black);
    paint.drawRect(0,0,rect().width()-1,rect().height()-1);
    paint.setFont(QFont("宋体",20));
    paint.drawText(QRect(0,0,rect().width()-1,rect().height()-1),Qt::AlignCenter,QString::number(num));
}

void MineItem::emitSignal()
{
    emit pressMineItem();
}
void MineItem::show(QWidget *pwidget)
{
    QPainter paint(pwidget);
    paint.setPen(Qt::black);
    paint.drawRect(0,0,rect().width()-1,rect().height()-1);
    paint.drawPixmap(QRect(2,2,rect().width()-2,rect().height()-2),QPixmap(":/bomb.png"));
}
