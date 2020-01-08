#ifndef ITEM_H
#define ITEM_H
#include<QWidget>
#include"ItemState.h"
class Item:public QWidget
{
  Q_OBJECT
private:
  ItemState *pState;
  QRect _rect;
public:
  enum ShowType
  {
      NORMAL_SHOW=0,
      AROUND_SHOW,
      DISABLE_SHOW
  };
  Item(ItemState *state,const QRect &rect,QWidget * parent=nullptr);
  void changeState(ItemState *state);
  void paintEvent(QPaintEvent *event);
  virtual void mousePressEvent(QMouseEvent *evt);
  ItemState * state();
  void changeState();
  ShowType AroundShow();
  void changeToOpenItem();



  virtual ~Item();

  bool flag;//访问标志
};
#endif
