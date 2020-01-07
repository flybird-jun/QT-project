#include"ItemState.h"
#include<QPainter>
ItemState::ItemState(ItemType *ptype)
{
    type = ptype;
}
ItemType * ItemState::GetItemType()
{
    return type;
}

void tipItem::show(QWidget *pwidget,const QRect &rect)
{
    QPainter paint(pwidget);
    paint.setPen(Qt::black);
    paint.drawRect(0,0,rect.width()-1,rect.height()-1);
    paint.drawPixmap(0,1,rect.width()-1,rect.height()-1,QPixmap(":/flag.png"));
}
void normalItem::show(QWidget *pwidget,const QRect &rect)
{
    QPainter paint(pwidget);
    paint.setPen(Qt::black);
    paint.setBrush(Qt::green);
    paint.drawRect(0,0,rect.width()-1,rect.height()-1);
}
/*
openItem::openItem(ItemType *ptype):ItemState(ptype)
{

}*/
void openItem::show(QWidget *pwidget,const QRect &rect)
{
    type->show(pwidget,rect);
}



