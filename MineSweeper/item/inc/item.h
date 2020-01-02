#ifndef ITEM_H
#define ITEM_H
#include"ItemState.h"
class Item:public QWidget
{
private:
  ItemState *pState;
public:
  Item(ItemState *state,QWidget * parent=nullptr);
  void paintEvent();
  void changeState(ItemState *state);
  void paintEvent(QPaintEvent *event);
  ItemState * state();
  virtual void mousePressEvent(QMouseEvent *evt);
  virtual ~Item();
};
#endif
