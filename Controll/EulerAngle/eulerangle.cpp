#include "eulerangle.h"
#include "ui_eulerangle.h"

EulerAngle::EulerAngle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EulerAngle)
{
    ui->setupUi(this);
}

EulerAngle::~EulerAngle()
{
    delete ui;
}
