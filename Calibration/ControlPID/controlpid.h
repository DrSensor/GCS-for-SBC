#ifndef CONTROLPID_H
#define CONTROLPID_H

#include <QWidget>
#include <QTimer>
#include "../../AddOn/qcustomplot.h"

namespace Ui {
class ControlPID;
}

class ControlPID : public QWidget
{
    Q_OBJECT
    
public:
    explicit ControlPID(QWidget *parent = 0);
    ~ControlPID();

    void setupRealtimeDataDemo(QCustomPlot *customPlot);
    
    double getP() const;
    double getI() const;
    double getD() const;

private:
    Ui::ControlPID *ui;

    QTimer dataTimer;
    double P,I,D;
    double value,error,desired;

private slots:
    void realtimeDataSlot();

public slots:
    void PIDupdatedSlider();
    void PIDupdatedSpinBox();

    void setErrorPlot(const double &error);
    void setValuePlot(const double &value);
    void setDesiredValue(const double &desired);

signals:
    void PIDchanged(const double &P, const double &I, const double &D);
};

#endif // CONTROLPID_H
