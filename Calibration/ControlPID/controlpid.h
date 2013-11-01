#ifndef CONTROLPID_H
#define CONTROLPID_H

#include <QWidget>

namespace Ui {
class ControlPID;
}

class ControlPID : public QWidget
{
    Q_OBJECT
    
public:
    explicit ControlPID(QWidget *parent = 0);
    ~ControlPID();
    
    double getP() const;
    double getI() const;
    double getD() const;

private:
    Ui::ControlPID *ui;
    double P,I,D;

public slots:
    void PIDupdatedSlider();
    void PIDupdatedSpinBox();

    void setErrorPlot(const double &);
    void setValuePlot(const double &);

signals:
    void PIDchanged(const double &P, const double &I, const double &D);
};

#endif // CONTROLPID_H
