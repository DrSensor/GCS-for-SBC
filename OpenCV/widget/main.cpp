#include "opencvwidget.h"
#include "opencvprocess.h"
#include <QApplication>
#include <QThreadPool>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OpenCVWidget w;
    OpenCVProcess *task = new OpenCVProcess();

    task->initialize(0);

    qRegisterMetaType<cv::Mat>("cv::Mat");
    QObject::connect(task, SIGNAL(processDone(cv::Mat)), &w, SLOT(showImage(cv::Mat)));
//    QObject::connect(&w, SIGNAL(cursorHover(QPoint)), task, SLOT(pointPixel(QPoint)));
//    QObject::connect(&w, SIGNAL(leftMouseButtonSelectArea(QPoint,QPoint)), task, SLOT(selectAreaRect(QPoint,QPoint)));
//    QObject::connect(&w, SIGNAL(imageSizeChanged(int,int)), task, SLOT(imageSizeChanged(int,int)));


    QThreadPool::globalInstance()->start(task);
    w.setMouseTracking(true);
    w.show();

    return a.exec();
}
