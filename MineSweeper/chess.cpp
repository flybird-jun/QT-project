#include "chess.h"
#include <QTime>
#include<QMessageBox>
ChessWidget::ChessWidget(int col,int row,int iCellWidth,QWidget *parent):QWidget(parent)
{
    CellWidth = iCellWidth;
    open_item_count = 0;
    this->row = row;
    this->col = col;
    num_item = row*col;
    mine_num = num_item/8;
    //ChessWidget width and height;
    int width = row*CellWidth;
    int height = col * CellWidth;
    resize(width,height);
    initItems();

}
void ChessWidget::initItems()
{
    QVector<QPoint>m_mines;
    //alloc m_items
    open_item_count = 0;
    m_items = new Item**[row];
    for(int i=0;i<col;i++)
        m_items[i] = new Item*[row];
    //雷随机位置
    for(int index=0;index<mine_num;index++)
    {
        int i = -1,j=-1;
        qsrand(QTime::currentTime().msec());
        i = qrand()/10%col;
        j = qrand()%row;
        if(m_mines.contains(QPoint(i,j)))
        {
            index--;
            continue;
        }
        else
        {
            m_mines.append(QPoint(i,j));
        }
    }

    //创建item对象
    //创建雷对象
    for(auto it:m_mines)
    {
        ItemType *type=new MineItem(QRect(it.y()*CellWidth,it.x()*CellWidth,CellWidth,CellWidth));
        ItemState * state = new normalItem(type);
        Item *pitem = new Item(state);
        m_items[it.x()][it.y()]=pitem;
        m_items[it.x()][it.y()]->setParent(this);
        m_items[it.x()][it.y()]->setVisible(true);//第二次初始化时，默认是不可见的
        connect(dynamic_cast<MineItem*>(type),&MineItem::pressMineItem,this,&ChessWidget::mineItemPressSlot);
    }
    //创建数字对象
    for(int i = 0;i<col;i++)
    {
        for(int j=0;j<row;j++)
        {
            //计算雷数
           if(!m_mines.contains(QPoint(i,j)))
            {
                int num = 0;
                for (int m=-1;m<=1;m++)
                {
                    for (int n=-1; n<=1;n++)
                    {
                        if (m==0 && n==0)
                        {
                            continue;
                        }
                        if(m_mines.contains(QPoint(i+m,j+n)))
                        {
                            num++;
                        }
                    }
                }
                ItemType *type=new NumItem(QRect(j*CellWidth,i*CellWidth,CellWidth,CellWidth),num);
                ItemState * state = new normalItem(type);
                Item *pitem = new Item(state);
                connect(dynamic_cast<NumItem*>(type),&NumItem::pressNumItem,this,&ChessWidget::numItemPressSlot);
                m_items[i][j] = pitem;
                m_items[i][j]->setParent(this);
                m_items[i][j]->setVisible(true);//第二次初始化时，默认是不可见的
           }
        }
     }
}
void ChessWidget::releaseItems()
{//先释放 type state
    for(int i = 0;i<col;i++)
    {
        for(int j = 0 ;j<row;j++)
        {
            //remove
            m_items[i][j]->setParent(nullptr);
            delete m_items[i][j]->state()->GetItemType();
            delete m_items[i][j]->state();
        }
    }
    for(int i=0;i<col;i++)
    {
        delete [] m_items[i];
    }
        delete [] m_items;
    m_items = nullptr;
}
void ChessWidget::openAround(int i,int j)
{

  //  if(m_items[i][j]->state()->GetItemType()->flag)
  //     return;

   // open_item_count ++;
    int around[4][2]={
            {-1,0},
            {1,0},
            {0,-1},
            {0,1}
    };

    for(int x=0;x<4;x++)
    {
        int a = around[x][0];
        int b = around[x][1];
        int p = i+a;
        if(p<0)
        {
            p=0;
        }
        if(p>col-1)
        {
            p=col-1;
        }
        int q = j+b;
        if(q<0)
        {
            q = 0;
        }
        if(q>row-1)
        {
            q=row-1;
        }
        ItemType *_item =m_items[p][q]->state()->GetItemType();
        if(_item->AroundShow()&&!_item->flag)
        {
            NumItem *pitem = dynamic_cast<NumItem *>(_item);
            ItemState*pState=m_items[p][q]->state();//->ItemStateChangeToOpenItem();
            m_items[p][q]->changeState(pState->ItemStateChangeToOpenItem());
            m_items[p][q]->state()->GetItemType()->disconnect();
            m_items[p][q]->state()->GetItemType()->flag = true;
            delete pState;
            open_item_count ++;
            if(pitem->number()==0)
            {
               openAround(p,q);
            }
        }
    }

}
void ChessWidget::numItemPressSlot(int num,QRect rect)
{

    int x = rect.x();
    int y = rect.y();
    int i = x/CellWidth;
    int j = y/CellWidth;
    open_item_count++;
    m_items[j][i]->state()->GetItemType()->flag = true;
    if(num == 0)
    {
        openAround(j,i);
    }

    if(open_item_count==num_item-mine_num)
    {
        emit GameWin();
    }
    repaint();
}

void ChessWidget::mineItemPressSlot()
{
    //show all
    for(int i = 0;i<col;i++)
    {
        for(int j = 0 ;j<row;j++)
        {
            ItemState *pState=m_items[i][j]->state();
            m_items[i][j]->changeState(pState->ItemStateChangeToOpenItem());
            delete pState;
        }
    }
    emit GameLoss();
}
ChessWidget::~ChessWidget()
{
    releaseItems();
}
