#include "controlpid.h"
#include "ui_controlpid.h"

ControlPID::ControlPID(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlPID)
{
    ui->setupUi(this);
}

ControlPID::~ControlPID()
{
    delete ui;
}
