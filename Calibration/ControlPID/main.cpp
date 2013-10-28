#include <QApplication>
#include "controlpid.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ControlPID w;
    w.show();
    
    return a.exec();
}
