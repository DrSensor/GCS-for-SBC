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
    
private:
    Ui::ControlPID *ui;
};

#endif // CONTROLPID_H
