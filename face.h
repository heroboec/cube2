#ifndef FACE_H
#define FACE_H
#include "polygon.h"

class Face
{
public:
    Face();
    Face(PointDDD& v1, PointDDD& v2, PointDDD& v3, PointDDD& v4 );
    ScreenPolygonFaceCoordsSruct& draw(double a, double b, double c, double d);
    Polygon& getNPolygon(int n);
    double getFaceLayer();



private:
    Polygon polOne;
    Polygon polTwo;
    ScreenPolygonFaceCoordsSruct ScreenPolygonFaceCoordsSructResult;
    double faceLayer;
    void calculateFaceLayer();



};

#endif // FACE_H
