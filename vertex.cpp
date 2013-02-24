#include "vertex.h"


Vertex::Vertex()
{
    this->position = PointDDD(0,0,0);
    this->normal = QVector3D(0.0,0.0,0.0);
}

Vertex::Vertex(PointDDD& pos)
{
    this->position = pos;
    this->normal = QVector3D(0.0,0.0,0.0);
}

void Vertex::setPos(PointDDD& point)
{
    this->position = point;
}
void Vertex::setPos(double x,double y,double z)
{
    PointDDD tmp(x,y,z);
    position = tmp;
}

void Vertex::setNormal(QVector3D& normal)
{
    this->normal = normal;
}

PointDDD &Vertex::getPos()
{
    return position;
}

const QVector3D &Vertex::getNormal()
{
    return normal;
}

Vertex::~Vertex()
{
//lololo
}
