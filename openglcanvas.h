#ifndef OPENGLCANVAS_H
#define OPENGLCANVAS_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>

class OpenGLCanvas : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    OpenGLCanvas(QWidget *parent = nullptr);
    ~OpenGLCanvas();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    QMatrix4x4 m_projection;
};

#endif // OPENGLCANVAS_H
