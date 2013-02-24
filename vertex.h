#ifndef VERTEX_H
#define VERTEX_H
#include <QVector3D>

#include "pointddd.h"

class Vertex
{
public:
    Vertex();
    Vertex(PointDDD&);
    ~Vertex();
    void setPos(PointDDD&);
    void setPos(double,double,double);
    void setNormal(QVector3D&);

    PointDDD &getPos();
    const QVector3D &getNormal();
private:
    PointDDD position;
    QVector3D normal;
};

#endif // VERTEX_H
