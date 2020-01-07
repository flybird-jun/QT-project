#include"item.h"
#include<QtDebug>
Item::Item(ItemState *state,const QRect &rect,QWidget * parent):QWidget(parent)
{
    pState = state;
    _rect = rect;
    resize(_rect.width(),_rect.height());
    move(_rect.x(),_rect.y());
    flag = false;
}
Item::ShowType Item::AroundShow()
{
    ItemType::ShowType __type = state()->GetItemType()->AroundShow();
    return (Item::ShowType)__type;
}
void Item::paintEvent(QPaintEvent *event)
{
    pState->show(this,_rect);
}
void Item::mousePressEvent(QMouseEvent *evt)
{
    if(evt->button()==Qt::RightButton)
    {
        changeState();
    }
    else if(evt->button()==Qt::LeftButton)
    {
        ItemType * _type = pState->GetItemType();
        changeToOpenItem();
        _type->emitSignal();//左键信号只能发射一次
       // _type->disconnect();
        evt->ignore();
    }
    qDebug()<<"event type"<<evt->x()<<" "<<evt->y()<<endl;
    //repaint();
}
void Item::changeToOpenItem()
{
    ItemState *newState = nullptr;
    ItemType * _type = pState->GetItemType();
    newState = new openItem(_type);
    delete pState;
    pState = newState;
}
void Item::changeState()
{
    ItemState *newState = nullptr;
    ItemType * _type = pState->GetItemType();
    if(typeid (*pState) == typeid(tipItem))
    {
        newState = new normalItem(_type);
    }
    else if(typeid(*pState)==typeid(normalItem))
    {
        newState = new tipItem(_type);
    }
    else
    {
        return;
    }
    delete pState;
    pState = newState;
}
void Item::changeState(ItemState *state)
{
    pState = state;
}
ItemState * Item::state()
{
    return pState;
}
Item::~Item()
{

}
