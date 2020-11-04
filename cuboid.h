#ifndef CUBOID_H
#define CUBOID_H

#include <qopengl.h>
#include <QVector>
#include <QVector3D>

class Cuboid
{
public:
    Cuboid();
    const GLfloat *constData() const { return m_data.constData(); }
    int count() const { return m_count; }
    int vertexCount() const { return m_count / 6; }

private:
    void quad(GLfloat x1, GLfloat y1,
              GLfloat x2, GLfloat y2,
              GLfloat x3, GLfloat y3,
              GLfloat x4, GLfloat y4,
              const QColor &c1,
              const QColor &c2);
    void extrude(GLfloat x1, GLfloat y1,
                 GLfloat x2, GLfloat y2,
                 const QColor &c);
    void add(const QVector3D &v, const QVector3D &n, const QColor &c);

    QVector<GLfloat> m_data;
    int m_count = 0;
};

#endif // CUBOID_H
