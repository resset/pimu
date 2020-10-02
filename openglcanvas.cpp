#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>

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
    //glDepthFunc(GL_LESS);
}

void OpenGLCanvas::resizeGL(int w, int h)
{
    m_projection.setToIdentity();
//    m_projection.viewport(0.0f, 0.0f, w, h);
//    m_projection.lookAt(QVector3D(0.0f, 1.0f, 3.0f),
//                        QVector3D(0.0f, 0.0f, 0.0f),
//                        QVector3D(0.0f, 1.0f, 0.0f));
    m_projection.perspective(70.0f, GLfloat(w) / GLfloat(h), 0.01f, 100.0f);
}

void drawBox(void)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

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

void OpenGLCanvas::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(xRotation, 1.0, 0.0, 0.0);
    glRotatef(yRotation, 0.0, 1.0, 0.0);
    glRotatef(zRotation, 0.0, 0.0, 1.0);

    drawBox();
}

void OpenGLCanvas::mousePressEvent(QMouseEvent *event)
{
    lastPosition = event->pos();
    xdiff = lastPosition.x() - yRotation;
    ydiff = -lastPosition.y() + xRotation;
    qInfo("XXX: %d, YYY: %d\n", event->x(), event->y());
}

void OpenGLCanvas::mouseMoveEvent(QMouseEvent *event)
{
//    int dx = event->x() - lastPosition.x();
//    int dy = event->y() - lastPosition.y();

    if (event->buttons() & Qt::LeftButton) {
        qInfo("x: %d, y: %d\n", event->x(), event->y());

        setXRotation(event->y() + xdiff);
        setYRotation(event->x() - ydiff);
    } else if (event->buttons() & Qt::RightButton) {
//        setXRotation(xRotation + 8 * dy);
//        setZRotation(zRotation + 8 * dx);
    }

    lastPosition = event->pos();
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0) {
        angle += 360;
    }
    while (angle > 360) {
        angle -= 360;
    }
}

void OpenGLCanvas::setXRotation(int angle)
{
    //qNormalizeAngle(angle);
    qDebug("X rotation: %d", angle);

    if (angle != xRotation) {
        xRotation = angle;
        //emit xRotationChanged(angle);
        update();
    }
}

void OpenGLCanvas::setYRotation(int angle)
{
    //qNormalizeAngle(angle);
    qDebug("Y rotation: %d", angle);

    if (angle != yRotation) {
        yRotation = angle;
        //emit yRotationChanged(angle);
        update();
    }
}

void OpenGLCanvas::setZRotation(int angle)
{
    //qNormalizeAngle(angle);
    qDebug("Z rotation: %d", angle);

    if (angle != zRotation) {
        zRotation = angle;
        //emit zRotationChanged(angle);
        update();
    }
}
