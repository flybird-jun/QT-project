#include"ItemType.h"
#include<QPainter>
#include<QWidget>
#include<QFont>
/*******************************************************NumItem************************************************/
NumItem::NumItem(int count):ItemType(count)
{

   // connect(this,&NumItem::NumItemSignal,);
}
void NumItem::emitSignal()
{
    emit NumItemSignal();
}
ItemType::ShowType NumItem::AroundShow()
{
    return NORMAL_SHOW;
}
void NumItem::show(QWidget *pwidget,const QRect &rect)
{
    QPainter paint(pwidget);
    paint.setPen(Qt::black);
    paint.drawRect(0,0,rect.width()-1,rect.height()-1);
    paint.setFont(QFont("宋体",20));
    paint.drawText(QRect(0,0,rect.width()-1,rect.height()-1),Qt::AlignCenter,QString::number(num));
}
/************************************************************************************************************/

/*******************************************************ZeroItem*********************************************/
ZeroItem::ZeroItem():ItemType(0)
{

}
void ZeroItem::emitSignal()
{
    emit ZeroItemSignal();
}
ItemType::ShowType ZeroItem::AroundShow()
{
    return NORMAL_SHOW;
}
void ZeroItem::show(QWidget *pwidget,const QRect &rect)
{
    QPainter paint(pwidget);
    paint.setPen(Qt::black);
    paint.drawRect(0,0,rect.width()-1,rect.height()-1);
}

/************************************************************************************************************/
MineItem::MineItem():ItemType(-1)
{

}
ItemType::ShowType MineItem::AroundShow()
{
    return DISABLE_SHOW;
}
void MineItem::emitSignal()
{
    emit MineItemSignal();
}
void MineItem::show(QWidget *pwidget,const QRect &rect)
{
    QPainter paint(pwidget);
    paint.setPen(Qt::black);
    paint.drawRect(0,0,rect.width()-1,rect.height()-1);
    paint.drawPixmap(QRect(2,2,rect.width()-2,rect.height()-2),QPixmap(":/bomb.png"));
}
