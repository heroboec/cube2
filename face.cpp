#include "face.h"
#include "polygon.h"

Face::Face()
{
}

Face::Face(PointDDD& v1, PointDDD& v2, PointDDD& v3, PointDDD& v4 )
{
    Vertex v1l = v1;
    Vertex v2l = v2;
    Vertex v3l = v3;
    Vertex v4l = v4;
    this->polOne=Polygon((v1l),(v2l),(v4l));
    this->polTwo=Polygon((v1l),(v3l),(v4l));
    calculateFaceLayer();
}



ScreenPolygonFaceCoordsSruct& Face::calculate(double a, double b, double c, double d)
{
    ScreenPolygonFaceCoordsSructResult.poly0 = polOne.calcCoords(a,b,c,d);
    ScreenPolygonFaceCoordsSructResult.poly1 = polTwo.calcCoords(a,b,c,d);
    calculateFaceLayer();
    return ScreenPolygonFaceCoordsSructResult;
}

Polygon& Face::getNPolygon(int n)
{
    if (n == 0)
    {
        return polOne;
    }
    else if (n == 1)
    {
        return polTwo;
    }
}


void Face::calculateFaceLayer()
{
    double tmpLayer = 0;
    tmpLayer += polOne.getLayout();
    tmpLayer += polTwo.getLayout();
    faceLayer = tmpLayer;
}

double Face::getFaceLayer()
{
    return this->faceLayer;
}
