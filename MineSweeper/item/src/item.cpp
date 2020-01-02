#include"item.h"
Item::Item(ItemState *state,QWidget * parent):QWidget(parent)
{
    pState = state;
    resize(pState->GetItemType()->rect().width(),pState->GetItemType()->rect().height());
    move(pState->GetItemType()->rect().x(),pState->GetItemType()->rect().y());
}
void Item::paintEvent(QPaintEvent *event)
{
    pState->show(this);
   // repaint();
}
void Item::mousePressEvent(QMouseEvent *evt)
{
    if(evt->button()==Qt::RightButton)
    {
       ItemState*iState=pState->ItemStateChange();
       delete pState;
       pState=iState;
    }
    else
    {
        ItemState*iState= pState->ItemStateChangeToOpenItem();;
        delete pState;
        pState=iState;
        pState->GetItemType()->__mousePressEvent(evt);
    }
    update();
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
