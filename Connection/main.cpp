#include <QApplication>
#include "connectiondialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    ConnectionDialog w;
    w.show();

    return a.exec();
}
