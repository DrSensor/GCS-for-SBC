#include "streaming.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Streaming w;
    w.show();
    
    return a.exec();
}
