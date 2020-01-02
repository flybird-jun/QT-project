#include"messageBox.h"
#include<QIcon>
MessageBox::MessageBox(QWidget *parent):QMessageBox(parent)
{
    setWindowTitle("提示信息");
 //   setWindowIcon(QIcon(":/win.png"));
    setAttribute(Qt::WA_DeleteOnClose);
  //  setText("你赢了！");
    addButton(tr("新游戏"),QMessageBox::YesRole);
    addButton(tr("返回"),QMessageBox::NoRole);
    resize(200,300);
}
