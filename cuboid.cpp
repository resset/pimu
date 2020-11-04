#include <qmath.h>
#include <qcolor.h>

#include "cuboid.h"

Cuboid::Cuboid()
{
    m_data.resize(2500 * 9);

    const GLfloat x1 = +0.2f;
    const GLfloat y1 = -0.1f;
    const GLfloat x2 = -0.2f;
    const GLfloat y2 = 0.1f;

    quad(x1, y1,
         x1, y2,
         x2, y2,
         x2, y1,
         QColorConstants::White,
         QColorConstants::Black);

    extrude(x1, y1, x1, y2, QColorConstants::Green);
    extrude(x1, y2, x2, y2, QColor(80, 80, 80, 0));
    extrude(x2, y2, x2, y1, QColorConstants::Red);
    extrude(x2, y1, x1, y1, QColor(80, 80, 80, 0));
}

void Cuboid::add(const QVector3D &v, const QVector3D &n, const QColor &c)
{
    GLfloat *p = m_data.data() + m_count;
    *p++ = v.x();
    *p++ = v.y();
    *p++ = v.z();
    *p++ = n.x();
    *p++ = n.y();
    *p++ = n.z();
    *p++ = c.redF();
    *p++ = c.greenF();
    *p++ = c.blueF();
    m_count += 9;
}

void Cuboid::quad(GLfloat x1, GLfloat y1,
                  GLfloat x2, GLfloat y2,
                  GLfloat x3, GLfloat y3,
                  GLfloat x4, GLfloat y4,
                  const QColor &c1,
                  const QColor &c2)
{
    QVector3D n = QVector3D::normal(QVector3D(x4 - x1, y4 - y1, 0.0f),
                                    QVector3D(x2 - x1, y2 - y1, 0.0f));

    add(QVector3D(x1, y1, -0.3f), n, c1);
    add(QVector3D(x4, y4, -0.3f), n, c1);
    add(QVector3D(x2, y2, -0.3f), n, c1);

    add(QVector3D(x3, y3, -0.3f), n, c1);
    add(QVector3D(x2, y2, -0.3f), n, c1);
    add(QVector3D(x4, y4, -0.3f), n, c1);

    n = QVector3D::normal(QVector3D(x1 - x4, y1 - y4, 0.0f),
                          QVector3D(x2 - x4, y2 - y4, 0.0f));

    add(QVector3D(x4, y4, 0.3f), n, c2);
    add(QVector3D(x1, y1, 0.3f), n, c2);
    add(QVector3D(x2, y2, 0.3f), n, c2);

    add(QVector3D(x2, y2, 0.3f), n, c2);
    add(QVector3D(x3, y3, 0.3f), n, c2);
    add(QVector3D(x4, y4, 0.3f), n, c2);
}

void Cuboid::extrude(GLfloat x1, GLfloat y1,
                     GLfloat x2, GLfloat y2,
                     const QColor &c)
{
    QVector3D n = QVector3D::normal(QVector3D(0.0f, 0.0f, -0.1f),
                                    QVector3D(x2 - x1, y2 - y1, 0.0f));

    add(QVector3D(x1, y1, +0.3f), n, c);
    add(QVector3D(x1, y1, -0.3f), n, c);
    add(QVector3D(x2, y2, +0.3f), n, c);

    add(QVector3D(x2, y2, -0.3f), n, c);
    add(QVector3D(x2, y2, +0.3f), n, c);
    add(QVector3D(x1, y1, -0.3f), n, c);
}
