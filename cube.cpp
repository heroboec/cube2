

#include <qmath.h>
#include <QtAlgorithms>
#include "cube.h"



cube::cube()
{
    init();
    m_cubeImage = QImage(QSize(m_cubeW,m_cubeH),QImage::Format_RGB32);
    m_cubePainter = new QPainter(&m_cubeImage);
    m_cubePainter->setBackground(Qt::black);
  // evaluateCube();

}

void cube::init()
{
    PointDDD tmp0 = PointDDD( 1, 1, 1);
    PointDDD tmp1 = PointDDD( 1,-1, 1);
    PointDDD tmp2 = PointDDD( 1, 1,-1);
    PointDDD tmp3 = PointDDD( 1,-1,-1);

    m_faces[0] = Face(tmp0,tmp1,tmp2,tmp3);

    tmp0 = PointDDD( 1,-1, 1);
    tmp1 = PointDDD(-1,-1, 1);
    tmp2 = PointDDD( 1,-1,-1);
    tmp3 = PointDDD(-1,-1,-1);

    m_faces[1] = Face(tmp0,tmp1,tmp2,tmp3);

    tmp0 = PointDDD(-1,-1, 1);
    tmp1 = PointDDD(-1, 1, 1);
    tmp2 = PointDDD(-1,-1,-1);
    tmp3 = PointDDD(-1, 1,-1);

    m_faces[2] = Face(tmp0,tmp1,tmp2,tmp3);

    tmp0 = PointDDD(-1, 1, 1);
    tmp1 = PointDDD( 1, 1, 1);
    tmp2 = PointDDD(-1, 1,-1);
    tmp3 = PointDDD( 1, 1,-1);


    m_faces[3] = Face(tmp0,tmp1,tmp2,tmp3);



    tmp0 = PointDDD( 1, 1, 1);
    tmp1 = PointDDD( 1,-1, 1);
    tmp2 = PointDDD(-1, 1, 1);
    tmp3 = PointDDD(-1,-1, 1);


    m_faces[4] = Face(tmp0,tmp1,tmp2,tmp3);



    tmp0 = PointDDD(-1,-1,-1);
    tmp1 = PointDDD(-1, 1,-1);
    tmp2 = PointDDD( 1,-1,-1);
    tmp3 = PointDDD( 1, 1,-1);
    m_faces[5] = Face(tmp0,tmp1,tmp2,tmp3);


    m_phi = 45;
    m_omega = 0;
    m_cubeW = 800;
    m_cubeH = 600;


    //lights

    m_lights.clear();
    lightSourceData lsd;  // =)
    lsd.amp = 0.51;
    lsd.color = QColor(Qt::red);
    lsd.pos = PointDDD(3,-2,6);
    m_lights.append(lsd);
    lsd.amp = 0.74;
    lsd.color = QColor(Qt::blue);
    lsd.pos = PointDDD(-5,-3,7);
    m_lights.append(lsd);
    lsd.amp = 0.32;
    lsd.color = QColor(Qt::yellow);
    lsd.pos = PointDDD(3,4,-6);
    m_lights.append(lsd);

    m_cubeCenter.setX(0);
    m_cubeCenter.setY(0);
    m_cubeCenter.setZ(0);


}



QVector3D& cube::createVectorByPoint(PointDDD& a,PointDDD& b)
{
    QVector3D *tmp = new QVector3D();
    tmp->setX(b.getX() - a.getX());
    tmp->setY(b.getY() - a.getY());
    tmp->setZ(b.getZ() - a.getZ());
    return *tmp;
}





void cube::evaluatePolygonsNormals()
{

}


//Vertex & cube::getDiffVert(Polygon &p1,Polygon &p2)
//{
//    int bingo;
//    for (int i=0;i<3;i++)
//    {
//        bingo = 0;
//        for (int k=0;k<3;k++)
//        {
//            if (p1.getVertNum(i) == p2.getVertNum(k))
//            {
//                bingo = 1;
//            }
//        }
//        if (bingo == 0 )
//        {
//            return m_cubeVertices[i];
//        }
//    }

//}


void cube::evaluateCube()
{
    double a = cos(m_phi/180);
    double b = sin(m_phi/180);

    double c = cos(m_omega/180);
    double d = sin(m_omega/180);
    QPen pen;
    pen.setColor(Qt::cyan);
    pen.setStyle(Qt::SolidLine);
    m_cubePainter->setPen(pen);
    clearCubeImage();
    QVector< Polygon > tmpScreenCoords;
   // tmpScreenCoords.clear();
    for (int i=0;i<6;i++)
    {
        ScreenPolygonFaceCoordsSruct tmp =  m_faces[i].draw(a,b,c,d);
//        tmpScreenCoords.append(tmp.poly0);
//        tmpScreenCoords.append(tmp.poly1);

        //рисуем не сразу и не все !!!
//        link(tmp.poly0.v0,tmp.poly0.v1);
//        link(tmp.poly0.v0,tmp.poly0.v2);
//        link(tmp.poly0.v2,tmp.poly0.v1);


//        link(tmp.poly0.v0,tmp.poly1.v1);
//        link(tmp.poly0.v0,tmp.poly1.v2);
//        link(tmp.poly0.v2,tmp.poly1.v1);
    }

    QVector< Polygon > tmpPolyArr;
    tmpPolyArr.clear();
    for (int j=0;j<6;j++)
    {
        tmpPolyArr.append(m_faces[j].getNPolygon(0));
        tmpPolyArr.append(m_faces[j].getNPolygon(1));

    }
    qSort(tmpPolyArr.begin(), tmpPolyArr.end(),order);
    for (int t=0;t<7;t++)
    {
        ScreenPolygonCoordsStruct tmp = tmpPolyArr[t].getScreenCords();
        link(tmp.v0,tmp.v1);
        link(tmp.v0,tmp.v2);
        link(tmp.v2,tmp.v1);
    }





//    static int linkArr[8][3]={{1,3,4},{0,2,5},{1,3,6},
//                              {0,2,7},{0,5,7},{1,4,6},
//                              {2,5,7},{3,4,6}};
    
//    PointDDD cubeV[8];
    
//    for (int i=0; i<VERTICESCNT; i++)
//    {
//        PointDDD tmp = m_cubeVertices[i].getPos();
//        cubeV[i].setX((-d)*tmp.getX() +
//                    c*tmp.getY());
        
//        cubeV[i].setY((-a)*c*tmp.getX() +
//                    -a*d*tmp.getY() +
//                    b*tmp.getZ());
        
//        cubeV[i].setZ((-b)*c*tmp.getX() +
//                    (-b)*d*tmp.getY() +
//                    (-a)*tmp.getZ() + 5
//                    );
//    }
//    for (int i = 0; i<VERTICESCNT;i++ )
//    {
//        m_screenCoord[i].setX(SCREENDIST*(cubeV[i].getX()/cubeV[i].getZ())+m_cubeW/2);
//        m_screenCoord[i].setY(SCREENDIST*(cubeV[i].getY()/cubeV[i].getZ())+m_cubeH/2);
//    }

//    QPen pen;
//    pen.setColor(Qt::cyan);
//    pen.setStyle(Qt::SolidLine);
//    m_cubePainter->setPen(pen);
//    clearCubeImage();
//    for (int i =0;i<VERTICESCNT;i++)
//    {
//        for (int k=0;k<3;k++)
//        {
//            link(m_screenCoord[i],m_screenCoord[linkArr[i][k]]);
//        }
//    }
    emit(repCube(m_cubeImage));
}








void cube::rotate(double omega, double phi)
{
    m_omega += omega;
    m_phi += phi;
    evaluateCube();
}


void cube::link(QPoint& p1,QPoint& p2)
{    
    m_cubePainter->drawLine(p1.x(),p1.y(),p2.x(),p2.y());
}

void cube::clearCubeImage()
{
    m_cubePainter->eraseRect(0,0,m_cubeW,m_cubeH);
    m_cubePainter->setBackground(Qt::black);
}


void cube::evaluateSimpleInt()
{
    for (int i=0;i<12;i++)
    {
        for (int k=0;k<m_lights.count();k++)
        {

        }
    }
}


bool cube::order(  Polygon & p1,  Polygon & p2 )
{
    return p1.getLayout() < p2.getLayout();
}





