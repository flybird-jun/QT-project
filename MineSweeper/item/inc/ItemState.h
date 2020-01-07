#ifndef ITEMSTATE_H
#define ITEMSTATE_H
#include"ItemType.h"
#include<QMainWindow>
class openItem;
class ItemState
{
protected:
    ItemType *type;
public:
    ItemState(ItemType *ptype);
    ItemType* GetItemType();
    virtual void show(QWidget *pwidget,const QRect &rect)=0;
    virtual ~ItemState(){}
};
class tipItem:public ItemState
{
public:
    using ItemState::ItemState;
    virtual void show(QWidget *pwidget,const QRect &rect);
   ~tipItem(){}
};
class normalItem:public ItemState
{
public:
    using ItemState::ItemState;
    virtual void show(QWidget *pwidget,const QRect &rect);
    ~normalItem(){}
};
class openItem:public ItemState
{
  public:
    //openItem(ItemType *ptype);
    using ItemState::ItemState;
    virtual void show(QWidget *pwidget,const QRect &rect);
    ~openItem(){}
};
#endif
