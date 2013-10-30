#ifndef OPENCVPROCESS_H
#define OPENCVPROCESS_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QRunnable>
#include <QObject>
#include <QPoint>

class OpenCVProcess : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit OpenCVProcess(QObject *parent = 0);
    void initialize(int n);
    void initialize(QString path);
    void run();
    cv::Mat getMat() const;

private:
    cv::Mat cv_frame;
    cv::VideoCapture cv_cap;
    int width, height;
    bool path_existed;

    void process (cv::Mat &cv_frame);

signals:
    void processDone( const cv::Mat &);
    bool processDone();

public slots:
    bool selectAreaRect( const QPoint &p1, const QPoint &p2);
    bool pointPixel( const QPoint &p);
    void imageSizeChanged( int outW, int outH ); /// Used to resize the image outside the widget
};

#endif // OPENCVPROCESS_H
