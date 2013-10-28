#include "opencvwidget.h"

#include <iostream>
#include <GL/glu.h>

OpenCVWidget::OpenCVWidget(QWidget *parent) :
    QGLWidget(parent)
{
    _width = 0;
    _height = 0;
    _texture = 0;
    select_object = false;
    select_done = false;
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
        std::cout << "GLWidget::paintGL: !!! Failed glTexImage2D" << std::endl;
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

    gluPerspective(53, 1, 1.0, 50.0);

    emit imageSizeChanged( width, height );

    gluLookAt(0.0,  0.0, 2.0,   // eye
              0.0,  0.0, 0.0,   // center
              0.0,  1.0, 0.0);  // up

    glMatrixMode(GL_MODELVIEW);  // Select the model view matrix
    glLoadIdentity();           // Reset the model view matrix
}

void OpenCVWidget::mouseMoveEvent(QMouseEvent *mouse)
{
    cv::Point origin;
    cv::Point mouse_in_pixel;

    {
        mouse_in_pixel.x = cv_frame.cols*mouse->x()/_width;
        mouse_in_pixel.y = cv_frame.rows*mouse->y()/_height;
    }

    if (select_object) {
        selection.x = MIN(mouse_in_pixel.x, origin.x);
        selection.y = MIN(mouse_in_pixel.y, origin.y);
        selection.width = std::abs(mouse_in_pixel.x - origin.x);
        selection.height = std::abs(mouse_in_pixel.y - origin.y);

        selection &= cv::Rect(0, 0, cv_frame.cols, cv_frame.rows);
    }
}

/*
void OpenCVWidget::mouseMoveEvent(QMouseEvent *mouse)
{
    static bool left_select = false, right_select = false;
    static bool left_once = true, right_once = true;
    QPoint left_pressed, right_pressed;
    QPoint left_released, right_released;

    if (mouse->button() == Qt::LeftButton) {
        emit leftMouseButtonPressed(mouse->pos());

        left_select = true;
        if (left_once) {
            left_pressed = mouse->pos();
            left_once = false;
        }
    }
    if (mouse->button() == Qt::RightButton) {
        emit rightMouseButtonPressed( mouse->pos() );

        right_select = true;
        if (right_once) {
            right_pressed = mouse->pos();
            right_once = false;
        }
    }

    if ( mouse->button() == Qt::NoButton ) {
        emit cursorHover( mouse->pos() );
        if (left_select) {
            left_released = mouse->pos();
            left_select = false;

            emit leftMouseButtonSelectArea( left_pressed, left_released );
        }
        if (right_select) {
            right_released = mouse->pos();
            right_select = false;

            emit rightMouseButtonSelectArea( right_pressed, right_released);
        }
        left_once = right_once = true;
    }
}
*/

void OpenCVWidget::mousePressEvent(QMouseEvent *mouse)
{
    cv::Point origin;
    cv::Point mouse_in_pixel;

    {
        mouse_in_pixel.x = cv_frame.cols*mouse->x()/_width;
        mouse_in_pixel.y = cv_frame.rows*mouse->y()/_height;
    }

    if (mouse->button() == Qt::LeftButton && !select_object) {
        selection = cv::Rect(mouse_in_pixel, cv::Point(0, 0));
        origin = mouse_in_pixel;
        select_object = true;
    }
}

void OpenCVWidget::mouseReleaseEvent(QMouseEvent *mouse)
{
    if( selection.width > 0 && selection.height > 0 )
        select_done = true;
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
        if( select_object && selection.width > 0 && selection.height > 0 )
        {
            roi = cv::Mat(cv_frame, selection);
            bitwise_not(roi, roi);
        }
        updateGL();
    }

    return true;
}
