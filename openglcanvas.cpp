#include "openglcanvas.h"

OpenGLCanvas::OpenGLCanvas(QWidget *parent)
    : QOpenGLWidget(parent)
{
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setSamples(10);
    //format.setVersion(4, 3);
    //format.setProfile(QSurfaceFormat::CoreProfile);
    setFormat(format);
}

OpenGLCanvas::~OpenGLCanvas()
{
}

void OpenGLCanvas::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.4f, 0.4f, 0.4f, 0.0f);
    glEnable(GL_DEPTH_TEST);
}

void OpenGLCanvas::resizeGL(int w, int h)
{
    m_projection.setToIdentity();
    m_projection.perspective(60.0f, w / float(h), 0.01f, 1000.0f);
}

void OpenGLCanvas::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBegin(GL_QUADS);

    // Left
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    glVertex3f(-0.5f, -0.5f, 1.0f);
    glVertex3f(-0.5f, 0.5f, 1.0f);
    glVertex3f(-0.5f, 0.5f, -1.0f);
    glVertex3f(-0.5f, -0.5f, -1.0f);

    // Right
    glColor3f(0.0f, 1.0f, 0.0f); // Green
    glVertex3f(0.5f, -0.5f, -1.0f);
    glVertex3f(0.5f, 0.5f, -1.0f);
    glVertex3f(0.5f, 0.5f, 1.0f);
    glVertex3f(0.5f, -0.5f, 1.0f);

    // Nose
    glColor3f(1.0f, 1.0f, 1.0f); // White
    glVertex3f(-0.5f, -0.5f, -1.0f);
    glVertex3f(0.5f, -0.5f, -1.0f);
    glVertex3f(0.5f, 0.5f, -1.0f);
    glVertex3f(-0.5f, 0.5f, -1.0f);

    // Tail
    glColor3f(0.0f, 0.0f, 0.0f); // Black
    glVertex3f(-0.5f, -0.5f, 1.0f);
    glVertex3f(0.5f, -0.5f, 1.0f);
    glVertex3f(0.5f, 0.5f, 1.0f);
    glVertex3f(-0.5f, 0.5f, 1.0f);

    // Top
    glColor3f(0.2f, 0.2f, 0.2f);
    glVertex3f(-0.5f, 0.5f, 1.0f);
    glVertex3f( 0.5f, 0.5f, 1.0f);
    glVertex3f( 0.5f, 0.5f, -1.0f);
    glVertex3f(-0.5f, 0.5f, -1.0f);

    // Bottom
    glColor3f(0.2f, 0.2f, 0.2f);
    glVertex3f(-0.5f, -0.5f, 1.0f);
    glVertex3f(-0.5f, -0.5f, -1.0f);
    glVertex3f( 0.5f, -0.5f, -1.0f);
    glVertex3f( 0.5f, -0.5f, 1.0f);

    glEnd();
}

void OpenGLCanvas::setXRotation(int angle)
{
    qDebug("X rotation: %d", angle);
}

void OpenGLCanvas::setYRotation(int angle)
{
    qDebug("Y rotation: %d", angle);
}

void OpenGLCanvas::setZRotation(int angle)
{
    qDebug("Z rotation: %d", angle);
}
