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

    setupRealtimeDataDemo(ui->value_plot);
    setupRealtimeDataDemo(ui->error_plot);
}

ControlPID::~ControlPID()
{
    delete ui;
}

void ControlPID::setupRealtimeDataDemo(QCustomPlot *customPlot)
{
    customPlot->addGraph(); // red line
    customPlot->graph(0)->setPen(QPen(Qt::red));
    customPlot->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
    customPlot->graph(0)->setAntialiasedFill(true);
    customPlot->addGraph(); // darkRed line
    customPlot->graph(1)->setPen(QPen(Qt::darkRed));
    customPlot->graph(0)->setChannelFillGraph(customPlot->graph(1));

    customPlot->addGraph(); // red dot
    customPlot->graph(2)->setPen(QPen(Qt::red));
    customPlot->graph(2)->setLineStyle(QCPGraph::lsNone);
    customPlot->graph(2)->setScatterStyle(QCPScatterStyle::ssDisc);
    customPlot->addGraph(); // darkRed dot
    customPlot->graph(3)->setPen(QPen(Qt::red));
    customPlot->graph(3)->setLineStyle(QCPGraph::lsNone);
    customPlot->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);

    customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    customPlot->xAxis->setDateTimeFormat("hh:mm:ss");
    customPlot->xAxis->setAutoTickStep(false);
    customPlot->xAxis->setTickStep(2);
    customPlot->axisRect()->setupFullAxesBox();

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer.start(0); // Interval 0 means to refresh as fast as possible
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

void ControlPID::setErrorPlot(const double &error)
{
    this->error = error;
}

void ControlPID::setValuePlot(const double &value)
{
    this->value = value;
}

void ControlPID::setDesiredValue(const double &desired)
{
    this->desired = desired;
}


void ControlPID::realtimeDataSlot()
{
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;

    static double lastPointKey = 0;
    if (key-lastPointKey > 0.01) // at most add point every 10 ms
    {
//      double value = qSin(key); //sin(key*1.6+cos(key*1.7)*2)*10 + sin(key*1.2+0.56)*20 + 26;
//      double error = qCos(key); //sin(key*1.3+cos(key*1.2)*1.2)*7 + sin(key*0.9+0.26)*24 + 26;
//      double yaw = qCos(key)+qSin(key); //sin(key*1.3+cos(key*1.2)*1.2)*7 + sin(key*0.9+0.26)*24 + 26;
      // add data to lines:
      ui->value_plot->graph(0)->addData(key, value);
      ui->value_plot->graph(1)->addData(key, desired);
      // set data of dots:
      ui->value_plot->graph(2)->clearData();
      ui->value_plot->graph(2)->addData(key, value);
      ui->value_plot->graph(3)->clearData();
      ui->value_plot->graph(3)->addData(key, desired);
      // remove data of lines that's outside visible range:
      ui->value_plot->graph(0)->removeDataBefore(key-8);
      ui->value_plot->graph(1)->removeDataBefore(key-8);
      // rescale value (vertical) axis to fit the current data:
      ui->value_plot->graph(0)->rescaleValueAxis(false, true);
      ui->value_plot->graph(1)->rescaleValueAxis(false, true);

      // add data to lines:
      ui->error_plot->graph(0)->addData(key, error);
      // set data of dots:
      ui->error_plot->graph(1)->clearData();
      ui->error_plot->graph(1)->addData(key, error);
      // remove data of lines that's outside visible range:
      ui->error_plot->graph(0)->removeDataBefore(key-8);
      // rescale value (vertical) axis to fit the current data:
      ui->error_plot->graph(0)->rescaleValueAxis(false, true);
      lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->value_plot->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
    ui->value_plot->replot();

    ui->error_plot->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
    ui->error_plot->replot();

    // calculate frames per second:
//    static double lastFpsKey;
//    static int frameCount;
//    ++frameCount;
//    if (key-lastFpsKey > 2) // average fps over 2 seconds
//    {
//      ui->statusBar->showMessage(
//            QString("%1 FPS, Total Data points: %2")
//            .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
//            .arg(ui->customPlot->graph(0)->data()->count()+ui->customPlot->graph(1)->data()->count())
//            , 0);
//      lastFpsKey = key;
//      frameCount = 0;
//    }
}
