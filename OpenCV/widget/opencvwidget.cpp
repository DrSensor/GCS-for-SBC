#include "opencvwidget.h"

#include <opencv2/highgui/highgui.hpp>
#include <GL/glu.h>
#include <QDebug>

OpenCVWidget::OpenCVWidget(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    _width = 0;
    _height = 0;
    _texture = 0;
    select_object = false;
}

OpenCVWidget::~OpenCVWidget()
{
    glDeleteTextures(1, &_texture);
}

void OpenCVWidget::initializeGL()
{
    makeCurrent();

    // Set clear color as black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Select pixel storage mode used by glTexImage2D
    glPixelStorei (GL_UNPACK_ALIGNMENT, 1);

    // Create the texture
    glGenTextures(1, &_texture);
}

void OpenCVWidget::paintGL()
{
    makeCurrent();

    // Clear the screen and depth buffer (with black)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Select the model view matrix and reset it
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, 0.0f);

    //    cv::cvtColor(cv_frame, cv_frame, CV_BGR2RGBA);

    glEnable(GL_TEXTURE_RECTANGLE_ARB);

    // Typical texture generation using data from the bitmap
    glBindTexture(GL_TEXTURE_RECTANGLE_ARB, _texture);

    // Transfer image data to the GPU
    glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0,
                 GL_RGB, cv_frame.cols, cv_frame.rows, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, cv_frame.data);

    if (glGetError() != GL_NO_ERROR)
    {
        qDebug() << "GLWidget::paintGL: !!! Failed glTexImage2D" << endl;
    }

    // Draw a 2D face with texture
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);                         glVertex2f(1.0, 1.0);
    glTexCoord2f(cv_frame.cols, 0);             glVertex2f(-1.0, 1.0);
    glTexCoord2f(cv_frame.cols, cv_frame.rows); glVertex2f(-1.0, -1.0);
    glTexCoord2f(0, cv_frame.rows);             glVertex2f(1.0, -1.0);
    glEnd();

    glDisable(GL_TEXTURE_RECTANGLE_ARB);
}

void OpenCVWidget::resizeGL(int width, int height)
{
    _width = width;
    _height = height;

    makeCurrent();

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);  // Select the projection matrix
    glLoadIdentity();             // Reset the projection matrix
    //    gluOrtho2D(0, width, 0, height); // set origin to bottom left corner

    gluPerspective(53, 1, _imgRatio, 50.0);
//    maintainAspectRatio(width, height);

    emit imageSizeChanged( width, height );

    gluLookAt(0.0,  0.0, 2.0,   // eye
              0.0,  0.0, 0.0,   // center
              0.0,  1.0, 0.0);  // up

    glMatrixMode(GL_MODELVIEW);  // Select the model view matrix
    glLoadIdentity();           // Reset the model view matrix
}

void OpenCVWidget::mouseMoveEvent(QMouseEvent *mouse)
{
    cv::Point mouse_in_pixel;

    {
        mouse_in_pixel.x = cv_frame.cols - cv_frame.cols*mouse->x()/_width;
        mouse_in_pixel.y = cv_frame.rows*mouse->y()/_height;
    }


    if (select_object) {
        qDebug() << "Mouse Select Pos : " << mouse_in_pixel.x << ", " << mouse_in_pixel.y << endl;
        if ( (mouse_in_pixel.x > 0 && mouse_in_pixel.x < cv_frame.cols)
                && (mouse_in_pixel.y > 0 && mouse_in_pixel.y < cv_frame.rows))
            selection = cv::Rect(origin, mouse_in_pixel);
    }
}

void OpenCVWidget::mousePressEvent(QMouseEvent *mouse)
{
    cv::Point mouse_in_pixel;

    {
        mouse_in_pixel.x = cv_frame.cols - cv_frame.cols*mouse->x()/_width;
        mouse_in_pixel.y = cv_frame.rows*mouse->y()/_height;
    }

    if (mouse->button() == Qt::LeftButton) {
        origin = mouse_in_pixel;
        select_object = true;
        selection = cv::Rect();
    }
}

void OpenCVWidget::mouseReleaseEvent(QMouseEvent *mouse)
{
    if (mouse->button() == Qt::LeftButton)
        select_object = false;
}

void OpenCVWidget::maintainAspectRatio(int width, int height)
{
    if (height == 0)  // Calculate aspect ratio of the window
        gluPerspective(53, (float) width, 1.0, 50.0);
    if (width == 0)
        gluPerspective(53, (float) height, 1.0, 50.0);
    else
        gluPerspective(53, (float) width / (float) height, 1.0, 50.0);
}

bool OpenCVWidget::showImage(const cv::Mat &image)
{
    if ( !(image.channels() == 1 || image.channels() == 3) ) return false;

    if (this->isVisible()) {
        cv_frame = image;
        _imgRatio = (float) cv_frame.cols / (float) cv_frame.rows;
        if( select_object && selection.width > 0 && selection.height > 0 )
        {
            qDebug() << "Selection Pos (x1,y1) : " << selection.x << ", " << selection.y << endl;
//            qDebug() << "Selection Size (x2,y2) : " << selection.x+selection.width << ", " << selection.y+selection.height << endl;
            roi = cv::Mat(cv_frame, selection);
            bitwise_not(roi, roi);
        }
        updateGL();
    }

    return true;
}
