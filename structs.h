#ifndef STRUCTS_H
#define STRUCTS_H
#include <QVector2D>

struct ScreenPolygonCoordsSruct
{
    QPoint v0;
    QPoint v1;
    QPoint v2;
};

struct ScreenPolygonFaceCoordsSruct
{
    ScreenPolygonCoordsSruct poly0;
    ScreenPolygonCoordsSruct poly1;
};



#endif // STRUCTS_H
