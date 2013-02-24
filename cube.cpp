

#include <qmath.h>

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



//    m_cubeVertices[0].setPos( 1.0,-1.0, 1.0);
//    m_cubeVertices[1].setPos( 1.0, 1.0, 1.0);
//    m_cubeVertices[2].setPos( 1.0, 1.0,-1.0);
//    m_cubeVertices[3].setPos( 1.0,-1.0,-1.0);

//    m_cubeVertices[4].setPos(-1.0,-1.0, 1.0);
//    m_cubeVertices[5].setPos(-1.0, 1.0, 1.0);
//    m_cubeVertices[6].setPos(-1.0, 1.0,-1.0);
//    m_cubeVertices[7].setPos(-1.0,-1.0,-1.0);


//    m_cubePolygons[0].setVert(1,0,3);
//    m_cubePolygons[1].setVert(1,3,2);
//    m_cubePolygons[2].setVert(1,2,6);
//    m_cubePolygons[3].setVert(1,6,5);
//    m_cubePolygons[4].setVert(1,5,4);
//    m_cubePolygons[5].setVert(1,4,0);
//    m_cubePolygons[6].setVert(7,0,4);
//    m_cubePolygons[7].setVert(7,3,0);
//    m_cubePolygons[8].setVert(7,2,3);
//    m_cubePolygons[9].setVert(7,6,2);
//    m_cubePolygons[10].setVert(7,5,6);
//    m_cubePolygons[11].setVert(7,4,5);

    evaluatePolygonsNormals();


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
    //   ,     1 ,   
    //           
//    for (int i=0;i<12;i+=2)
//    {
//        QVector3D a = createVectorByPoint(
//                    m_cubeVertices[m_cubePolygons[i].getVertNum(0)].getPos(),
//                    m_cubeVertices[m_cubePolygons[i].getVertNum(1)].getPos());
//        QVector3D b = createVectorByPoint(
//                    m_cubeVertices[m_cubePolygons[i].getVertNum(0)].getPos(),
//                    m_cubeVertices[m_cubePolygons[i].getVertNum(2)].getPos());
//      //  a.normalize();
//      //  b.normalize();
//        QVector3D normal = QVector3D::crossProduct(a,b);
//        normal.normalize();
//        m_cubePolygons[i].setNormal(normal);
//        m_cubePolygons[i+1].setNormal(normal);
//        for (int k=0;k<m_lights.count(); k++)
//        {
//            float distToLight = 1/createVectorByPoint(m_cubeCenter,m_lights[k].pos).length();
//            QVector3D v;
//            v.setX(0);
//            v.setY(0);
//            v.setZ(-2);

//        }


////        //  -  ,   ,
////        //        )))
////        for (int k=0; k<3;k++)
////        {
////            QVector3D norm =
////                    m_cubeVertices[m_cubePilygons[i].getVertNum(k)].getNormal();
////            norm.setX(norm.x()+normal.x());
////            norm.setZ(norm.z()+normal.z());
////            norm.setY(norm.y()+normal.y());
////            m_cubeVertices[m_cubePilygons[i].getVertNum(k)].setNormal(norm);
////        }
////        Vertex diff  = getDiffVert(m_cubePilygons[i],m_cubePilygons[i+1]);

//    }






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

    for (int i=0;i<6;i++)
    {
        ScreenPolygonFaceCoordsSruct tmp =  m_faces[i].draw(a,b,c,d);
        link(tmp.poly0.v0,tmp.poly0.v1);
        link(tmp.poly0.v0,tmp.poly0.v2);
        link(tmp.poly0.v2,tmp.poly0.v1);


        link(tmp.poly0.v0,tmp.poly1.v1);
        link(tmp.poly0.v0,tmp.poly1.v2);
        link(tmp.poly0.v2,tmp.poly1.v1);
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
        //           ?)))
        // ,    ,     )



        for (int k=0;k<m_lights.count();k++)
        {

        }
    }
}



//=========================



//======================================




