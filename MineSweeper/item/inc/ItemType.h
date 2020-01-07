#ifndef __ITEM_TYPE_H
#define __ITEM_TYPE_H
#include<QApplication>
#include<QMouseEvent>
#include<QRect>
class ItemType:public QObject
{
    Q_OBJECT
protected:
    int num;
public:
   // bool flag;
   // ItemType()
    enum ShowType
    {
        NORMAL_SHOW=0,
        AROUND_SHOW,
        DISABLE_SHOW
    };
    ItemType(int count){num=count;}
    virtual void show(QWidget *pwidget,const QRect &rect)=0;
    virtual ShowType AroundShow() = 0;
    virtual void emitSignal()=0;
    virtual ~ItemType(){};
};
class NumItem:public ItemType
{
   Q_OBJECT
signals:
    void NumItemSignal();
public:
    NumItem(int count);
    virtual void emitSignal();
    virtual void show(QWidget *pwidget,const QRect &rect);
    virtual ShowType AroundShow();
    ~NumItem(){}
};
class ZeroItem:public ItemType
{
  Q_OBJECT
signals:
    void ZeroItemSignal();
public:
    ZeroItem();
    virtual void emitSignal();
    virtual void show(QWidget *pwidget,const QRect &rect);
    virtual ShowType AroundShow();
    ~ZeroItem(){}

};
class MineItem:public ItemType
{
    Q_OBJECT
signals:
    void MineItemSignal();
public:
    MineItem();
    virtual void emitSignal();
    virtual void show(QWidget *pwidget,const QRect &rect);
     virtual ShowType AroundShow();
    ~MineItem(){};
};
#endif
