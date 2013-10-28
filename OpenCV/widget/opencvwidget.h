#ifndef OPENCVWIDGET_H
#define OPENCVWIDGET_H

#include <opencv2/core/core.hpp>
#include <QGLWidget>
#include <QMouseEvent>

class OpenCVWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit OpenCVWidget(QWidget *parent = 0);
    virtual ~OpenCVWidget();

    /* OpenGL initialization, viewport resizing, and painting */

    void initializeGL();
    void paintGL();
    void resizeGL( int width, int height);

protected:
    void mouseMoveEvent(QMouseEvent *mouse);
    void mousePressEvent(QMouseEvent *mouse);
    void mouseReleaseEvent(QMouseEvent *mouse);

private:
    int _width;
    int _height;
    double _imgRatio;
    bool select_object;
    bool select_done;
    cv::Rect selection;
    cv::Mat cv_frame;
    cv::Mat roi;
    GLuint _texture;

    void maintainAspectRatio(int width, int height);
    
signals:
    void imageSizeChanged( int outW, int outH ); /// Used to resize the image outside the widget

    void leftMouseButtonPressed( const QPoint &);
    void rightMouseButtonPressed( const QPoint &);

    void leftMouseButtonSelectArea( const QPoint &, const QPoint &);
    void rightMouseButtonSelectArea( const QPoint &, const QPoint &);

    void cursorHover( const QPoint & );

public slots:
    bool showImage( const cv::Mat &image ); /// Used to set the image to be viewed

    
};

#endif // OPENCVWIDGET_H
