// BUG : graphicsview not very reliable change another one like QtSLAM

#ifndef SLAM_H
#define SLAM_H

#include <QWidget>

namespace Ui {
class SLAM;
}

class SLAM : public QWidget
{
    Q_OBJECT
    
public:
    explicit SLAM(QWidget *parent = 0);
    ~SLAM();
    
private:
    Ui::SLAM *ui;
};

#endif // SLAM_H
