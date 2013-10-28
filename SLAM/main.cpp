#include <QApplication>
#include "slam.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SLAM w;
    w.show();
    
    return a.exec();
}
