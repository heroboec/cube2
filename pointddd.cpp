#include "pointddd.h"

PointDDD::PointDDD()
{
    m_x = 0.0;
    m_y = 0.0;
    m_z = 0.0;
}

PointDDD::PointDDD(float x,float y ,float z):m_x(x),m_y(y),m_z(z)
{
}

void PointDDD::setX(float x)
{
    m_x = x;
}

void PointDDD::setY(float y)
{
    m_y = y;
}

void PointDDD::setZ(float z)
{
    m_z = z;
}
void PointDDD::setPoint(float x, float y, float z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}

float PointDDD::getX() const
{
    return m_x;
}

float PointDDD::getY() const
{
    return m_y;
}

float PointDDD::getZ() const
{
    return m_z;
}
