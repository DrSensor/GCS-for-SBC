#include "camshift.h"
#include "ui_camshift.h"

#include <QThreadPool>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

// BUG : promote QGLWidget to QWidget

CamShift::CamShift(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CamShift)
{
    ui->setupUi(this);

    task = new OpenCVProcess(this);
//    cam = new OpenCVWidget(this);

    task->initialize(0);

//    connect(task, SIGNAL(processDone(cv::Mat)), cam, SLOT(showImage(cv::Mat)));
    connect(task, SIGNAL(processDone(cv::Mat)), ui->image, SLOT(showImage(cv::Mat)));
    QThreadPool::globalInstance()->start(task);

//    ui->formLayout->addWidget(cam);
}

CamShift::~CamShift()
{
    delete ui;
}

void CamShift::showImage(const cv::Mat &img)
{
//    cam->showImage(img);
    cv::imshow("test",img);
}
