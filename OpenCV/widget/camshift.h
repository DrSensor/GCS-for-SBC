#ifndef CAMSHIFT_H
#define CAMSHIFT_H

#include "opencvwidget.h"
#include "opencvprocess.h"
#include <QWidget>

namespace Ui {
class CamShift;
}

class CamShift : public QWidget
{
    Q_OBJECT
    
public:
    explicit CamShift(QWidget *parent = 0);
    ~CamShift();
    
private:
    Ui::CamShift *ui;

    OpenCVProcess *task;
//    OpenCVWidget *cam;

public slots:
    void showImage(const cv::Mat &img);
};

#endif // CAMSHIFT_H
