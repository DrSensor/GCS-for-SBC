#include "ahrs.h"
#include "ui_ahrs.h"

AHRS::AHRS(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AHRS)
{
    ui->setupUi(this);
}

AHRS::~AHRS()
{
    delete ui;
}
