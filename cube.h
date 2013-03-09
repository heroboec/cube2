#ifndef CUBE_H
#define CUBE_H
#include <QObject>
#include <QGraphicsScene>

#include <QPainter>
#include <QImage>
#include <QDebug>
#include <QVector>
#include <QVector3D>


#include "face.h"

//struct lightsData
//{
//    double Ka,Kd,Ks,Ns;
//    QVector3D N,L,V,R;
//};

struct lightSourceData
{
    QColor color;
    PointDDD pos;
    double amp;
};

class cube:public QObject
{
    Q_OBJECT
private:
    double a,b,c,d;
    QVector< PointDDD > m_visLightPos;
    float m_amb;
    float m_spec;
    float m_diff;
    QVector< QPoint > m_screenLighsPos;
    QVector< Face > m_faceArr;
    enum {VERTICESCNT=8, SCREENDIST=300};
    void link(QPoint& p1,QPoint& p2);
   // Vertex m_cubeVertices[8];
   // Polygon m_cubePolygons[12];
    Face m_faces[6];

    double m_phi;
    double m_omega;
    QImage m_cubeImage;
    QPainter *m_cubePainter;
    int m_cubeW;
    int m_cubeH;
    QVector< lightSourceData > m_lights;
    PointDDD m_cubeCenter;


    void init();
    static bool order(  Face &p1,  Face &p2 );
    static bool pointCompare(QPoint& pnt1, QPoint& pnt2);
    void clearCubeImage();
    //double getIntensity(lightsData &ldata);
    QVector3D& createVectorByPoint(PointDDD& a,PointDDD& b);
//    Vertex & getDiffVert(Polygon &p1,Polygon &p2);

    void evaluatePolygonsNormals();
    void evaluateSimpleInt();
    void drawFace(Face& fce);
    void drawFaceColor(Face &fce, QColor &color);
    double getDegree( double  cosin );
    void drawPolyColor(Polygon & poly, QColor& color);

    QVector3D getReflVector(QVector3D& v, QVector3D& n);
    QVector3D getCameraVector(PointDDD& polyPoint);

    
public:
    void evaluateCube();
    cube();
public slots:
    void rotate(double omega, double phi);

signals:
    void repCube(QImage& img);

    
};

#endif // CUBE_H
