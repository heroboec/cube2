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




ScreenPolygonCoordsStruct& Polygon::calcCoords(double a, double b, double c, double d)
{
    for (int i=0; i<3; i++)
    {
        PointDDD tmp = m_worldVertexes[i].getPos();
        m_visualVertexes[i].setPos((-d)*tmp.getX()+c*tmp.getY(),
                    (-a)*c*tmp.getX()+(-a)*d*tmp.getY()+b*tmp.getZ(),
                    (-b)*c*tmp.getX()+(-b)*d*tmp.getY()+(-a)*tmp.getZ() + 5);
    }

    for (int i = 0; i<3;i++ )
    {
        m_screenCoord[i].setX(300*(m_visualVertexes[i].getPos().getX()/
                m_visualVertexes[i].getPos().getZ())+
                800/2);
        m_screenCoord[i].setY(300*(m_visualVertexes[i].getPos().getY()/
                                   m_visualVertexes[i].getPos().getZ())+600/2);
    }
    calculateNormal();

//    QVector3D aVect = createVectorByPoint(
//                m_worldVertexes[0].getPos(),
//                m_worldVertexes[1].getPos());
//    QVector3D bVect = createVectorByPoint(
//                m_worldVertexes[0].getPos(),
//                m_worldVertexes[2].getPos());


//    QVector3D normal = QVector3D::crossProduct(aVect,bVect);
//    normal.normalize();
//    m_normal = normal;
    screenCoordsSructResult.v0 = m_screenCoord[0];
    screenCoordsSructResult.v1 = m_screenCoord[1];
    screenCoordsSructResult.v2 = m_screenCoord[2];
    calculateLayout();
    return getScreenCords();
}


ScreenPolygonCoordsStruct & Polygon::getScreenCords()
{
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


void Polygon::calculateLayout()
{
    double summ = 0;
    for (int i=0;i<3;i++)
    {
        summ += m_visualVertexes[i].getPos().getZ();
    }
    layout = summ/3;
}

double Polygon::getLayout()
{
    return layout;
}

void Polygon::calculateNormal()
{
    double x1 = m_worldVertexes[0].getPos().getX();
    double x2 = m_worldVertexes[1].getPos().getX();
    double x3 = m_worldVertexes[2].getPos().getX();

    double y1 = m_worldVertexes[0].getPos().getY();
    double y2 = m_worldVertexes[1].getPos().getY();
    double y3 = m_worldVertexes[2].getPos().getY();

    double z1 = m_worldVertexes[0].getPos().getZ();
    double z2 = m_worldVertexes[1].getPos().getZ();
    double z3 = m_worldVertexes[2].getPos().getZ();


    double A = y1*(z2 - z3) + y2*(z3 - z1) + y3*(z1 - z2);
    double B =  z1*(x2 - x3) + z2*(x3 - x1) + z3*(x1 - x2) ;
    double C = x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2);
    double D = x1*(y2*z3 - y3*z2) + x2*(y3*z1 - y1*z3) + x3*(y1*z2 - y2*z1);
    D*=-1;

    if (D > 0)
    {
        m_normal.setX((-1)*A);
        m_normal.setY((-1)*B);
        m_normal.setZ((-1)*C);
    }
    else
    {
        m_normal.setX(A);
        m_normal.setY(B);
        m_normal.setZ(C);
    }
    m_normal.normalize();

}
