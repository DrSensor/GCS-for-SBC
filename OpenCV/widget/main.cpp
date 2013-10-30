//#include "opencvprocess.h"
//#include "opencvwidget.h"
#include "camshift.h"
#include <QApplication>
#include <QThreadPool>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CamShift w;
//    OpenCVProcess *task = new OpenCVProcess();
//    OpenCVWidget gl;

//    task->initialize(0);
    qRegisterMetaType<cv::Mat>("cv::Mat");
//    QThreadPool::globalInstance()->start(task);
//    QObject::connect(task, SIGNAL(processDone(cv::Mat)), &gl, SLOT(showImage(cv::Mat)));
//    gl.show();

//    QObject::connect(&w, SIGNAL(cursorHover(QPoint)), task, SLOT(pointPixel(QPoint)));
//    QObject::connect(&w, SIGNAL(leftMouseButtonSelectArea(QPoint,QPoint)), task, SLOT(selectAreaRect(QPoint,QPoint)));
//    QObject::connect(&w, SIGNAL(imageSizeChanged(int,int)), task, SLOT(imageSizeChanged(int,int)));


    w.show();

    return a.exec();
}
