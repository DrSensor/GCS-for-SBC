#include "ahrs.h"
#include "ui_ahrs.h"

AHRS::AHRS(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AHRS)
{
    ui->setupUi(this);

    setupRealtimeDataDemo(ui->plot);
}

AHRS::~AHRS()
{
    delete ui;
}

void AHRS::setupRealtimeDataDemo(QCustomPlot *customPlot)
{
    customPlot->addGraph(); // blue line
    customPlot->graph(0)->setPen(QPen(Qt::blue));
//    customPlot->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
    customPlot->graph(0)->setAntialiasedFill(false);
    customPlot->addGraph(); // red line
    customPlot->graph(1)->setPen(QPen(Qt::red));
//    customPlot->graph(0)->setChannelFillGraph(customPlot->graph(1));
    customPlot->addGraph(); // green line
    customPlot->graph(2)->setPen(QPen(Qt::green));
//    customPlot->graph(1)->setChannelFillGraph(customPlot->graph(2));

    customPlot->addGraph(); // blue dot
    customPlot->graph(3)->setPen(QPen(Qt::blue));
    customPlot->graph(3)->setLineStyle(QCPGraph::lsNone);
    customPlot->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);
    customPlot->addGraph(); // red dot
    customPlot->graph(4)->setPen(QPen(Qt::red));
    customPlot->graph(4)->setLineStyle(QCPGraph::lsNone);
    customPlot->graph(4)->setScatterStyle(QCPScatterStyle::ssDisc);
    customPlot->addGraph(); // green dot
    customPlot->graph(5)->setPen(QPen(Qt::green));
    customPlot->graph(5)->setLineStyle(QCPGraph::lsNone);
    customPlot->graph(5)->setScatterStyle(QCPScatterStyle::ssDisc);

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

void AHRS::setValue(const double &pitch, const double &roll, const double &yaw)
{
    this->pitch = pitch; this->roll = roll; this->yaw = yaw;
}

void AHRS::realtimeDataSlot()
{
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;

    static double lastPointKey = 0;
    if (key-lastPointKey > 0.01) // at most add point every 10 ms
    {
//      double pitch = qSin(key); //sin(key*1.6+cos(key*1.7)*2)*10 + sin(key*1.2+0.56)*20 + 26;
//      double roll = qCos(key); //sin(key*1.3+cos(key*1.2)*1.2)*7 + sin(key*0.9+0.26)*24 + 26;
//      double yaw = qCos(key)+qSin(key); //sin(key*1.3+cos(key*1.2)*1.2)*7 + sin(key*0.9+0.26)*24 + 26;
      // add data to lines:
      ui->plot->graph(0)->addData(key, pitch);
      ui->plot->graph(1)->addData(key, roll);
      ui->plot->graph(2)->addData(key, yaw);
      // set data of dots:
      ui->plot->graph(3)->clearData();
      ui->plot->graph(3)->addData(key, pitch);
      ui->plot->graph(4)->clearData();
      ui->plot->graph(4)->addData(key, roll);
      ui->plot->graph(5)->clearData();
      ui->plot->graph(5)->addData(key, yaw);
      // remove data of lines that's outside visible range:
      ui->plot->graph(0)->removeDataBefore(key-8);
      ui->plot->graph(1)->removeDataBefore(key-8);
      ui->plot->graph(2)->removeDataBefore(key-8);
      // rescale value (vertical) axis to fit the current data:
      ui->plot->graph(0)->rescaleValueAxis(false, true);
      ui->plot->graph(1)->rescaleValueAxis(false, true);
      ui->plot->graph(2)->rescaleValueAxis(false, true);
      lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->plot->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
    ui->plot->replot();

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
