#ifndef OPENGLCANVAS_H
#define OPENGLCANVAS_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>

#include "cuboid.h"

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class OpenGLCanvas : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    OpenGLCanvas(QWidget *parent = nullptr);
    ~OpenGLCanvas();

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void cleanup();

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    void setupVertexAttribs();

    int m_xRot = 0;
    int m_yRot = 0;
    int m_zRot = 0;
    QPoint m_lastPos;
    Cuboid m_cuboid;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_cuboidVbo;
    QOpenGLShaderProgram *m_program = nullptr;
    int m_projMatrixLoc = 0;
    int m_mvMatrixLoc = 0;
    int m_normalMatrixLoc = 0;
    int m_lightPosLoc = 0;
    QMatrix4x4 m_proj;
    QMatrix4x4 m_camera;
    QMatrix4x4 m_world;
};

#endif // OPENGLCANVAS_H
