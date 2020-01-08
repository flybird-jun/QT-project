#include "chess.h"
#include <QTime>
#include "ItemType.h"
#include<QMessageBox>
#include <QPoint>
ChessWidget::ChessWidget(int col,int row,int iCellWidth,QWidget *parent):QWidget(parent)
{
    CellWidth = iCellWidth;
    open_item_count = 0;
    this->row = row;
    this->col = col;
    num_item = row*col;
    mine_num = 20;//num_item/8;
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
  //  m_items = new Item**[row];
 //   for(int i=0;i<col;i++)
   //     m_items[i] = new Item*[row];
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
    for(int i = 0;i<col;i++)
    {
        QVector<Item *> line;
        for(int j=0;j<row;j++)
        {
             ItemType *type = nullptr;
            if(m_mines.contains(QPoint(i,j)))
            {//创建雷对象
                type=new MineItem();
                connect(dynamic_cast<MineItem*>(type),&MineItem::MineItemSignal,this,&ChessWidget::mineItemSlot);
            }
            else
            {//创建数字对象
                //计算周围雷数
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
                if(num==0)
                {
                   type=new ZeroItem();
                   connect(dynamic_cast<ZeroItem*>(type),&ZeroItem::ZeroItemSignal,this,&ChessWidget::zeroItemSlot);
                }
                else
                {
                    type=new NumItem(num);
                    connect(dynamic_cast<NumItem*>(type),&NumItem::NumItemSignal,this,&ChessWidget::numItemSlot);
                }
            }
            ItemState * state = new normalItem(type);
            Item *pitem = new Item(state,QRect(j*CellWidth,i*CellWidth,CellWidth,CellWidth));
            pitem->setParent(this);
            pitem->setVisible(true);
            line.push_back(pitem);
        }
        m_items.push_back(line);
    }

}
void ChessWidget::releaseItems()
{//释放 type state

    for(auto it=m_items.begin();it!=m_items.end();it++)
    {
        for(auto _it:*it)
        {
            _it->setParent(nullptr);
            delete _it->state()->GetItemType();//ItemType
            delete _it->state();//ItemState
            delete _it;//Item
        }
        it->clear();
    }
    m_items.clear();
}
void ChessWidget::openAround(int i,int j)
{
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
        if(m_items[p][q]->AroundShow()!=Item::DISABLE_SHOW&&!m_items[p][q]->flag)
        {
                coordinate.setX(p);
                coordinate.setY(q);
                m_items[p][q]->changeToOpenItem();
                m_items[p][q]->state()->GetItemType()->emitSignal();
        }
    }

}

void ChessWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
       QPoint pos = event->pos();
       coordinate.setX(pos.y()/CellWidth);
       coordinate.setY(pos.x()/CellWidth);
       m_items[coordinate.x()][coordinate.y()]->state()->GetItemType()->emitSignal();
       m_items[coordinate.x()][coordinate.y()]->state()->GetItemType()->disconnect();
       event->accept();
    }
}

void ChessWidget::numItemPress()
{

    open_item_count++;
    m_items[coordinate.x()][coordinate.y()]->flag = true;
    if(open_item_count==num_item-mine_num)
    {
        emit GameWin();
    }
}
void ChessWidget::zeroItemSlot()
{
    numItemPress();
    openAround(coordinate.x(),coordinate.y());
    repaint();
}
void ChessWidget::numItemSlot()
{
    numItemPress();
    repaint();
}

void ChessWidget::mineItemSlot()
{
    //show all
    for(auto it:m_items)
    {
        for(auto _it:it)
        {
            _it->changeToOpenItem();
        }
    }
    emit GameLoss();
}
ChessWidget::~ChessWidget()
{
    releaseItems();
}
