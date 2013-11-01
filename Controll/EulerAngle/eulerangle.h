#ifndef EULERANGLE_H
#define EULERANGLE_H

#include <QWidget>

namespace Ui {
class EulerAngle;
}

class EulerAngle : public QWidget
{
    Q_OBJECT
    
public:
    explicit EulerAngle(QWidget *parent = 0);
    ~EulerAngle();
    
private:
    Ui::EulerAngle *ui;
};

#endif // EULERANGLE_H
