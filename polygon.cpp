#include "polygon.h"

Polygon::Polygon()
{
//    this->m_worldVertexes[0] = Vertex(PointDDD(0,0,0));
//    this->m_worldVertexes[1] = 0;
//    this->m_worldVertexes[2] = 0;
    m_polygonIntense=0;
}

void Polygon::setNormal(QVector3D& norm)
{
    m_normal = norm;
}

//void Polygon::setVert(int a,int b,int c)
//{
//    vertexes[0] = a;
//    vertexes[1] = b;
//    vertexes[2] = c;
//}

const QVector3D &Polygon::getNormal()
{
    return m_normal;
}

//int Polygon::getVertNum(int i)
//{
//    return this->vertexes[i];
//}

void Polygon::setPolyInt(double i)
{
    m_polygonIntense = i;
}

double Polygon::getPolyInt()
{
    return m_polygonIntense;
}


Polygon::Polygon(Vertex& v1, Vertex& v2, Vertex& v3)
{
    this->m_worldVertexes[0] = v1;
    this->m_worldVertexes[1] = v2;
    this->m_worldVertexes[2] = v3;
}




ScreenPolygonCoordsSruct& Polygon::calcCoords(double a, double b, double c, double d)
{
    for (int i=0; i<3; i++)
    {
        PointDDD tmp = m_worldVertexes[i].getPos();
        m_visualVertexes[i].setPos((-d)*tmp.getX()+c*tmp.getY(),
                    (-a)*c*tmp.getX()+(-a)*d*tmp.getY()+b*tmp.getZ(),
                    (-b)*c*tmp.getX()+(-b)*d*tmp.getY()+(-a)*tmp.getZ() + 5);

//        cubeV[i].setY((-a)*c*tmp.getX() +
//                    -a*d*tmp.getY() +
//                    b*tmp.getZ());

//        cubeV[i].setZ((-b)*c*tmp.getX() +
//                    (-b)*d*tmp.getY() +
//                    (-a)*tmp.getZ() + 5
//                    );
    }

    for (int i = 0; i<3;i++ )
    {
        m_screenCoord[i].setX(300*(m_visualVertexes[i].getPos().getX()/
                m_visualVertexes[i].getPos().getZ())+
                800/2);
        m_screenCoord[i].setY(300*(m_visualVertexes[i].getPos().getY()/
                                   m_visualVertexes[i].getPos().getZ())+600/2);
    }

    QVector3D aVect = createVectorByPoint(
                m_worldVertexes[0].getPos(),
                m_worldVertexes[1].getPos());
    QVector3D bVect = createVectorByPoint(
                m_worldVertexes[0].getPos(),
                m_worldVertexes[2].getPos());

    QVector3D normal = QVector3D::crossProduct(aVect,bVect);
    normal.normalize();
    m_normal = normal;
    screenCoordsSructResult.v0 = m_screenCoord[0];
    screenCoordsSructResult.v1 = m_screenCoord[1];
    screenCoordsSructResult.v2 = m_screenCoord[2];
    return screenCoordsSructResult;
}




QVector3D& Polygon::createVectorByPoint(PointDDD& a,PointDDD& b)
{
    QVector3D *tmp = new QVector3D();
    tmp->setX(b.getX() - a.getX());
    tmp->setY(b.getY() - a.getY());
    tmp->setZ(b.getZ() - a.getZ());
    return *tmp;
}
