#include<QOpenGLWidget>
class Mplayer:public QOpenGLWidget
{
 public:
    Mplayer();
    void paintEvent(QPaintEvent *e);
};
