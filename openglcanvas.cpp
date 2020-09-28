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
}

void OpenGLCanvas::resizeGL(int w, int h)
{
    m_projection.setToIdentity();
    m_projection.perspective(60.0f, w / float(h), 0.01f, 1000.0f);
}

void OpenGLCanvas::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
