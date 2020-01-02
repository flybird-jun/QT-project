#include<QWidget>
#include"item.h"
class ChessWidget:public QWidget
{
    Q_OBJECT
private:
    Item* **m_items;
    int mine_num;
    int num_item;
    int open_item_count;
    int row;
    int col;
    int CellWidth;
signals:
    void GameWin();
    void GameLoss();
public slots:
    void numItemPressSlot();
    void mineItemPressSlot();
public:
    ChessWidget(int col,int row,int CellWidth,QWidget *parent);
    void initItems();
    void releaseItems();
    virtual ~ChessWidget();
   // void paintEvent(QPaintEvent *event);
};
