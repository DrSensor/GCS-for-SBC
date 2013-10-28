#include <QApplication>
#include "ahrs.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AHRS w;
    w.show();
    
    return a.exec();
}
