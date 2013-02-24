#ifndef STRUCTS_H
#define STRUCTS_H
#include <QVector2D>

struct ScreenPolygonCoordsStruct
{
    QPoint v0;
    QPoint v1;
    QPoint v2;
};

struct ScreenPolygonFaceCoordsSruct
{
    ScreenPolygonCoordsStruct poly0;
    ScreenPolygonCoordsStruct poly1;
};



#endif // STRUCTS_H
