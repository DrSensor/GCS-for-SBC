#ifndef AHRS_H
#define AHRS_H

#include <QWidget>
#include <QTimer>
#include "../AddOn/qcustomplot.h"

namespace Ui {
class AHRS;
}

class AHRS : public QWidget
{
    Q_OBJECT
    
public:
    explicit AHRS(QWidget *parent = 0);
    ~AHRS();

    void setupRealtimeDataDemo(QCustomPlot *customPlot);
    
public slots:
    void setValue(const double &pitch, const double &roll, const double &yaw);

private slots:
    void realtimeDataSlot();

private:
    Ui::AHRS *ui;

    QTimer dataTimer;
    double pitch,roll,yaw;
};

#endif // AHRS_H
