#include<QMessageBox>
class MessageBox:public QMessageBox
{
    Q_OBJECT
public:
    MessageBox(QWidget *parent = nullptr);
    ~MessageBox(){};
};
