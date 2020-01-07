#include<QWidget>
#include"item.h"
#include<QVector>
class ChessWidget:public QWidget
{
    Q_OBJECT
private:
    QVector<QVector<Item *>>m_items;
    int mine_num;
    int num_item;
    int open_item_count;
    int row;
    int col;
    int CellWidth;

    QPoint coordinate;//记录 左键m_items下标
protected:
    void numItemPress();
signals:
    void GameWin();
    void GameLoss();
public slots:
    void numItemSlot();
    void mineItemSlot();
    void zeroItemSlot();
public:
    ChessWidget(int col,int row,int CellWidth,QWidget *parent);
    virtual void mousePressEvent(QMouseEvent *event) override;
    void initItems();
    void releaseItems();
    void openAround(int i,int j);
    virtual ~ChessWidget();
   // void paintEvent(QPaintEvent *event);
};
