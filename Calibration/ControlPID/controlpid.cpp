#include "controlpid.h"
#include "ui_controlpid.h"

ControlPID::ControlPID(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlPID)
{
    ui->setupUi(this);

    connect(ui->P_slider, SIGNAL(valueChanged(int)), this, SLOT(PIDupdatedSlider()));
    connect(ui->I_slider, SIGNAL(valueChanged(int)), this, SLOT(PIDupdatedSlider()));
    connect(ui->D_slider, SIGNAL(valueChanged(int)), this, SLOT(PIDupdatedSlider()));

    connect(ui->P_spinBox, SIGNAL(valueChanged(double)), this, SLOT(PIDupdatedSpinBox()));
    connect(ui->I_spinBox, SIGNAL(valueChanged(double)), this, SLOT(PIDupdatedSpinBox()));
    connect(ui->D_spinBox, SIGNAL(valueChanged(double)), this, SLOT(PIDupdatedSpinBox()));
}

ControlPID::~ControlPID()
{
    delete ui;
}

void ControlPID::PIDupdatedSlider()
{
    ui->P_spinBox->setValue(ui->P_slider->value());
    ui->I_spinBox->setValue(ui->I_slider->value());
    ui->D_spinBox->setValue(ui->D_slider->value());

    P = ui->P_spinBox->value(); I = ui->I_spinBox->value(); D = ui->D_spinBox->value();
    emit PIDchanged(P, I, D);
}

void ControlPID::PIDupdatedSpinBox()
{
    ui->P_slider->setValue(ui->P_spinBox->value());
    ui->I_slider->setValue(ui->I_spinBox->value());
    ui->D_slider->setValue(ui->D_spinBox->value());

    P = ui->P_spinBox->value(); I = ui->I_spinBox->value(); D = ui->D_spinBox->value();
    emit PIDchanged(P, I, D);
}

void ControlPID::setErrorPlot(const double &)
{
}

void ControlPID::setValuePlot(const double &)
{
}
