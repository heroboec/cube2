#ifndef FACE_H
#define FACE_H
#include "polygon.h"

class Face
{
public:
    Face();
    Face(PointDDD& v1, PointDDD& v2, PointDDD& v3, PointDDD& v4 );
    ScreenPolygonFaceCoordsSruct& draw(double a, double b, double c, double d);

private:
    Polygon polOne;
    Polygon polTwo;
    ScreenPolygonFaceCoordsSruct ScreenPolygonFaceCoordsSructResult;

};

#endif // FACE_H
