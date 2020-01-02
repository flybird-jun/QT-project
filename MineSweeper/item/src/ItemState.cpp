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
openItem* ItemState::ItemStateChangeToOpenItem()
{
    ItemType *m_type = GetItemType();
    return new openItem(m_type);
}
ItemState* tipItem::ItemStateChange()
{
    return new normalItem(type);
}
void tipItem::show(QWidget *pwidget)
{
    QPainter paint(pwidget);
    paint.setPen(Qt::black);
    paint.drawRect(0,0,type->rect().width()-1,type->rect().height()-1);
    paint.drawPixmap(0,1,type->rect().width()-1,type->rect().height()-1,QPixmap(":/flag.png"));
}
void normalItem::show(QWidget *pwidget)
{
    QPainter paint(pwidget);
    paint.setPen(Qt::black);
    paint.setBrush(Qt::green);
    paint.drawRect(0,0,type->rect().width()-1,type->rect().height()-1);
}
ItemState* normalItem::ItemStateChange()
{
    return new tipItem(type);
}
void openItem::show(QWidget *pwidget)
{
    type->show(pwidget);
}
ItemState* openItem::ItemStateChange()
{
    return new openItem(type);
}



