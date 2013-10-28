#include <QApplication>
#include "navigation.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Navigation w;
    w.show();
    
    return a.exec();
}
