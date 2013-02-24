#ifndef POLYGON_H
#define POLYGON_H

#include <QVector2D>
#include "structs.h"
#include "vertex.h"

class Polygon
{
private:
    //int vertexes[3];
    QVector3D m_normal;
    double m_polygonIntense;
    Vertex m_worldVertexes[3];
    Vertex m_visualVertexes[3];
    QPoint m_screenCoord[3];
    ScreenPolygonCoordsStruct screenCoordsSructResult;
    double layout;

    void calculateNormal();

public:
    Polygon();
    double getLayout();
    Polygon(Vertex& v1, Vertex& v2, Vertex& v3);
    ScreenPolygonCoordsStruct &calcCoords(double a, double b, double c, double d);
    void setPolyInt(double);
    double getPolyInt();
    void setNormal(QVector3D& norm);
    QVector3D& createVectorByPoint(PointDDD& a,PointDDD& b);
    void calculateLayout();
    ScreenPolygonCoordsStruct & getScreenCords();
    //void setVert(int a,int b,int c);

    const QVector3D &getNormal();
    //int getVertNum(int i);
};

#endif // POLYGON_H
