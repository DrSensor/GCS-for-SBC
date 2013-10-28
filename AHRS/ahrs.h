#ifndef AHRS_H
#define AHRS_H

// osgQt

#include <QWidget>

namespace Ui {
class AHRS;
}

class AHRS : public QWidget
{
    Q_OBJECT
    
public:
    explicit AHRS(QWidget *parent = 0);
    ~AHRS();
    
private:
    Ui::AHRS *ui;
};

#endif // AHRS_H
