#ifndef OPENGLCANVAS_H
#define OPENGLCANVAS_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>

class OpenGLCanvas : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    OpenGLCanvas(QWidget *parent = nullptr);
    ~OpenGLCanvas();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

private:
    QMatrix4x4 m_projection;

    QPoint lastPosition;
    int xdiff = 0;
    int ydiff = 0;
    GLfloat xRotation = 0.0f;
    GLfloat yRotation = 0.0f;
    GLfloat zRotation = 0.0f;
};

#endif // OPENGLCANVAS_H
