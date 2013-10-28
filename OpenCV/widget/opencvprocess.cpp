#include "opencvprocess.h"

#include <QString>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

OpenCVProcess::OpenCVProcess(QObject *parent) :
    QObject(parent)
{
    path_existed = false;
}

void OpenCVProcess::initialize(int n)
{
    cv_cap.open(n);
    cv_cap.set(CV_CAP_PROP_CONVERT_RGB, 1);
    if ( !cv_cap.isOpened() ) cout << "can't open camera" << endl;
}

void OpenCVProcess::initialize(QString path)
{
    cv_frame = imread(path.toStdString());
    path_existed = true;
}

void OpenCVProcess::run()
{
    while (cv_cap.isOpened()) {
        cv_cap >> cv_frame;

        process(cv_frame);

        emit processDone(cv_frame);
    }

    if (path_existed) {
        process(cv_frame);
        emit processDone(cv_frame);
    }
}

void OpenCVProcess::process(Mat &cv_frame)
{
    // insert code for image processing here
    cvtColor(cv_frame, cv_frame, CV_BGR2RGB);
}

bool OpenCVProcess::selectAreaRect( const QPoint &p1, const QPoint &p2)
{
    QPoint t1, t2;
    t1 = QPoint(cv_frame.cols*p1.x()/width, cv_frame.rows*p1.y()/height);
    t2 = QPoint(cv_frame.cols*p2.x()/width, cv_frame.rows*p2.y()/height);

    return true;
}

bool OpenCVProcess::pointPixel(const QPoint &p)
{
    QPoint t;
    t = QPoint(cv_frame.cols*p.x()/width, cv_frame.rows*p.y()/height);

    return true;
}

void OpenCVProcess::imageSizeChanged(int outW, int outH)
{
    width = outW; height = outH;
}
