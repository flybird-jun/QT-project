#include "mainwindow.h"

#include <QApplication>
#include "decode/decode.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //DecodeThread* thread = new DecodeThread();
    //thread->start();
    w.show();
    return a.exec();
}
