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
    virtual void show(QWidget *pwidget)=0;
    virtual ItemState* ItemStateChange()=0;//右键
    virtual openItem* ItemStateChangeToOpenItem();//左键
    virtual ~ItemState(){}
};
class tipItem:public ItemState
{
public:
    using ItemState::ItemState;
    ItemState* ItemStateChange();
    virtual void show(QWidget *pwidget);
   ~tipItem(){}
};
class normalItem:public ItemState
{
public:
    using ItemState::ItemState;
    ItemState* ItemStateChange();
    virtual void show(QWidget *pwidget);
    ~normalItem(){}
};
class openItem:public ItemState
{
  public:
    openItem(ItemType *ptype);
    ItemState* ItemStateChange();
    virtual void show(QWidget *pwidget);
    ~openItem(){}
};
#endif
